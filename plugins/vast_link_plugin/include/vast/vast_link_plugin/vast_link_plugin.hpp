/**
 *  @file
 *  @copyright defined in vast/LICENSE.txt
 */
#pragma once
#include <vast/http_plugin/http_plugin.hpp>
#include <vast/chain_plugin/chain_plugin.hpp>

#include <appbase/application.hpp>
#include <vast/chain/controller.hpp>

namespace vast {
using vast::chain::controller;
using namespace appbase;

class vast_link_plugin : public plugin<vast_link_plugin> {
public:
    APPBASE_PLUGIN_REQUIRES((chain_plugin)(http_plugin))

    vast_link_plugin();
    virtual ~vast_link_plugin();

    virtual void set_program_options(options_description&, options_description&) override;

    void plugin_initialize(const variables_map&);
    void plugin_startup();
    void plugin_shutdown();

private:
    std::shared_ptr<class vast_link_plugin_impl> my_;
};

}  // namespace vast
