/**
 *  @file
 *  @copyright defined in vast/LICENSE.txt
 */
#pragma once
#include <vast/vast_plugin/vast_plugin.hpp>
#include <vast/http_plugin/http_plugin.hpp>

#include <appbase/application.hpp>
#include <vast/chain/controller.hpp>

namespace vast {
using vast::chain::controller;
using std::unique_ptr;
using namespace appbase;

class vast_api_plugin : public plugin<vast_api_plugin> {
public:
    APPBASE_PLUGIN_REQUIRES((chain_plugin)(http_plugin)(vast_plugin))

    vast_api_plugin();
    virtual ~vast_api_plugin();

    virtual void set_program_options(options_description&, options_description&) override;

    void plugin_initialize(const variables_map&);
    void plugin_startup();
    void plugin_shutdown();

private:
    unique_ptr<class vast_api_plugin_impl> my;
};

}  // namespace vast
