/**
 *  @file
 *  @copyright defined in vast/LICENSE.txt
 */
#pragma once
#include <vast/chain_plugin/chain_plugin.hpp>
#include <vast/http_client_plugin/http_client_plugin.hpp>

#include <appbase/application.hpp>
#include <vast/chain/controller.hpp>

namespace vast {
using vast::chain::controller;
using namespace appbase;

class staking_plugin : public plugin<staking_plugin> {
public:
    APPBASE_PLUGIN_REQUIRES((chain_plugin)(http_client_plugin))

    staking_plugin();
    virtual ~staking_plugin();

    virtual void set_program_options(options_description&, options_description&) override;

    void plugin_initialize(const variables_map&);
    void plugin_startup();
    void plugin_shutdown();

private:
    std::shared_ptr<class staking_plugin_impl> my_;
};

}  // namespace vast
