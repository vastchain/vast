/**
 *  @file
 *  @copyright defined in vast/LICENSE.txt
 */
#include <vast/vast_link_plugin/vast_link_plugin.hpp>

#include <deque>
#include <tuple>
#include <chrono>
#include <unordered_map>
#include <thread>

#include <boost/asio.hpp>
#include <fc/io/json.hpp>
#include <fc/crypto/city.hpp>

#include <vast/chain_plugin/chain_plugin.hpp>
#include <vast/chain/plugin_interface.hpp>
#include <vast/chain/exceptions.hpp>
#include <vast/chain/types.hpp>
#include <vast/chain/contracts/vast_link.hpp>
#include <vast/chain/contracts/vast_link_object.hpp>

namespace vast {

static appbase::abstract_plugin& _vast_link_plugin = app().register_plugin<vast_link_plugin>();

using vast::chain::bytes;
using vast::chain::link_id_type;
using vast::chain::block_state_ptr;
using vast::chain::transaction_trace_ptr;
using vast::chain::contracts::vast_link;
using vast::chain::contracts::everipay;

using boost::asio::steady_timer;
using steady_timer_ptr = std::shared_ptr<steady_timer>;

struct vast_link_id_hasher {
    size_t
    operator()(const link_id_type& id) const {
        return fc::city_hash_size_t((const char*)&id, sizeof(id));
    }
};

class vast_link_plugin_impl : public std::enable_shared_from_this<vast_link_plugin_impl> {
public:
    using deferred_pair = std::pair<deferred_id, steady_timer_ptr>;
    enum { kDeferredId = 0, kTimer };

public:
    vast_link_plugin_impl(controller& db)
        : db_(db) {}
    ~vast_link_plugin_impl();

public:
    void init();
    void get_trx_id_for_link_id(const link_id_type& link_id, deferred_id id);
    void add_and_schedule(const link_id_type& link_id, deferred_id id);

private:
    void applied_block(const block_state_ptr& bs);

    template<typename T>
    void response(const link_id_type& link_id, T&& response_fun);

public:
    controller& db_;

    std::atomic_bool init_{false};
    uint32_t         timeout_;

    std::unordered_multimap<link_id_type, deferred_pair, vast_link_id_hasher> link_ids_;

    std::optional<boost::signals2::scoped_connection> accepted_block_connection_;
};

void
vast_link_plugin_impl::applied_block(const block_state_ptr& bs) {
    if(link_ids_.empty()) {
        return;
    }

    for(auto& trx : bs->trxs) {
        for(auto& act : trx->packed_trx->get_transaction().actions) {
            if(act.name != N(everipay)) {
                continue;
            }

            auto& epact = act.data_as<const everipay&>();

            response(epact.link.get_link_id(), [&] {
                auto vo         = fc::mutable_variant_object();
                vo["block_num"] = bs->block_num;
                vo["block_id"]  = bs->id;
                vo["trx_id"]    = trx->id;
                vo["err_code"]  = 0;

                return fc::json::to_string(vo);
            });
        }
    }
}

template<typename T>
void
vast_link_plugin_impl::response(const link_id_type& link_id, T&& response_fun) {
    auto sz = link_ids_.count(link_id);
    if(sz == 0) {
        return;
    }
    auto json = response_fun();
    auto wptr = std::weak_ptr<vast_link_plugin_impl>(shared_from_this());
    boost::asio::post(app().get_io_service(), [wptr, json, link_id] {
        auto self = wptr.lock();
        if(!self) {
            return;
        }
        auto pair = self->link_ids_.equal_range(link_id);
        if(pair.first != self->link_ids_.end()) {
            std::for_each(pair.first, pair.second, [&](auto& it) {
                app().get_plugin<http_plugin>().set_deferred_response(std::get<kDeferredId>(it.second), 200, json);
            });

            self->link_ids_.erase(link_id);
            return;
        }
    });
}

void
vast_link_plugin_impl::add_and_schedule(const link_id_type& link_id, deferred_id id) {
    auto it = link_ids_.emplace(link_id, std::make_pair(id, std::make_shared<steady_timer>(app().get_io_service())));

    auto timer = std::get<kTimer>(it->second);
    timer->expires_from_now(std::chrono::milliseconds(timeout_));
    
    auto wptr = std::weak_ptr<vast_link_plugin_impl>(shared_from_this());
    timer->async_wait([wptr, link_id](auto& ec) {
        auto self = wptr.lock();
        if(self && ec != boost::asio::error::operation_aborted) {
            auto pair = self->link_ids_.equal_range(link_id);
            if(pair.first == self->link_ids_.end()) {
                wlog("Cannot find context for id: ${id}", ("id",link_id));
                return;
            }
            
            auto ids = std::vector<deferred_id>();
            std::for_each(pair.first, pair.second, [&ids](auto& it) {
                ids.emplace_back(std::get<kDeferredId>(it.second));
            });

            self->link_ids_.erase(link_id);

            try {
                VAST_THROW(chain::exceed_vast_link_watch_time_exception, "Exceed VAST-Link watch time: ${time} ms", ("time",self->timeout_));
            }
            catch(...) {
                http_plugin::handle_exception("vast_link", "get_trx_id_for_link_id", "", [&ids](auto code, auto body) {
                    for(auto id : ids) {
                        app().get_plugin<http_plugin>().set_deferred_response(id, code, body);
                    }
                });
            }
        }
    });
}

void
vast_link_plugin_impl::get_trx_id_for_link_id(const link_id_type& link_id, deferred_id id) {
    // try to fetch from chain first
    try {
        auto obj = db_.get_link_obj_for_link_id(link_id);
        if(obj.block_num > db_.fork_db_head_block_num()) {
            // block not finalize yet
            add_and_schedule(link_id, id);
            return;
        }

        auto vo         = fc::mutable_variant_object();
        vo["block_num"] = obj.block_num;
        vo["block_id"]  = db_.get_block_id_for_num(obj.block_num);
        vo["trx_id"]    = obj.trx_id;

        app().get_plugin<http_plugin>().set_deferred_response(id, 200, fc::json::to_string(vo));
    }
    catch(const chain::vast_link_existed_exception&) {
        // cannot find now, put into map
        add_and_schedule(link_id, id);
    }
}

void
vast_link_plugin_impl::init() {
    init_ = true;

    auto& chain_plug = app().get_plugin<chain_plugin>();
    auto& chain      = chain_plug.chain();

    accepted_block_connection_.emplace(chain.accepted_block.connect([&](const chain::block_state_ptr& bs) {
        applied_block(bs);
    }));
}

vast_link_plugin_impl::~vast_link_plugin_impl() {}

vast_link_plugin::vast_link_plugin() {}
vast_link_plugin::~vast_link_plugin() {}

void
vast_link_plugin::set_program_options(options_description&, options_description& cfg) {
    cfg.add_options()
        ("vast-link-timeout", bpo::value<uint32_t>()->default_value(5000), "Max time waitting for the deferred request.")
    ;
}

void
vast_link_plugin::plugin_initialize(const variables_map& options) {
    my_ = std::make_shared<vast_link_plugin_impl>(app().get_plugin<chain_plugin>().chain());
    my_->timeout_ = options.at("vast-link-timeout").as<uint32_t>();
    my_->init();
}

void
vast_link_plugin::plugin_startup() {
    ilog("starting vast_link_plugin");

    app().get_plugin<http_plugin>().add_deferred_handler("/v1/vast_link/get_trx_id_for_link_id", [&](auto, auto body, auto id) {
        try {
            auto var = fc::json::from_string(body);
            auto b   = bytes();
            fc::from_variant(var["link_id"], b);

            if(b.size() != sizeof(link_id_type)) {
                VAST_THROW(chain::vast_link_id_exception, "VAST-Link id is not in proper length");
            }

            auto link_id = link_id_type();
            memcpy(&link_id, b.data(), sizeof(link_id_type));

            my_->get_trx_id_for_link_id(link_id, id);
        }
        catch(...) {
            http_plugin::handle_exception("vast_link", "get_trx_id_for_link_id", body, [id](auto code, auto body) {
                app().get_plugin<http_plugin>().set_deferred_response(id, code, body);
            });
        }
    });

    my_->init_ = false;
}

void
vast_link_plugin::plugin_shutdown() {
    my_->accepted_block_connection_.reset();
    my_.reset();
}

}  // namespace vast
