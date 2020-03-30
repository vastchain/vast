/**
 *  @file
 *  @copyright defined in vast/LICENSE.txt
 */
#pragma once
#include <appbase/application.hpp>
#include <vast/chain_plugin/chain_plugin.hpp>
#include <vast/chain/types.hpp>
#include <vast/chain/contracts/types.hpp>

namespace fc {
class variant;
}  // namespace fc

namespace vast {

namespace chain {
class controller;
}  // namespace chain

class vast_plugin;

namespace vast_apis {

using namespace vast::chain;
using namespace vast::chain::contracts;

class read_only {
public:
    read_only(const controller& db)
        : db_(db) {}

public:
    struct get_domain_params {
        domain_name name;
    };
    fc::variant get_domain(const get_domain_params& params);

    struct get_group_params {
        group_name name;
    };
    fc::variant get_group(const get_group_params& params);

    struct get_token_params {
        domain_name domain;
        token_name  name;
    };
    fc::variant get_token(const get_token_params& params);

    struct get_tokens_params {
        domain_name        domain;
        std::optional<int> skip;
        std::optional<int> take;
    };
    fc::variant get_tokens(const get_tokens_params& params);

    struct get_fungible_params {
        symbol_id_type id;
    };
    fc::variant get_fungible(const get_fungible_params& params);

    struct get_fungible_balance_params {
        address_type                  address;
        std::optional<symbol_id_type> sym_id;
    };
    fc::variant get_fungible_balance(const get_fungible_balance_params& params);

    struct get_fungible_psvbonus_params {
        symbol_id_type id;
    };
    fc::variant get_fungible_psvbonus(const get_fungible_psvbonus_params& params);

    struct get_suspend_params {
        proposal_name name;
    };
    fc::variant get_suspend(const get_suspend_params& params);

    using get_lock_params = get_suspend_params;
    fc::variant get_lock(const get_lock_params& params);

    struct get_stakepool_params {
        symbol_id_type sym_id;
    };
    fc::variant get_stakepool(const get_stakepool_params& params);

    struct get_validator_params {
        account_name name;
    };
    fc::variant get_validator(const get_validator_params& params);

    struct get_staking_shares_params{
        address_type address;
    };
    fc::variant get_staking_shares(const get_staking_shares_params& params);

    struct get_vastlink_signed_keys_params {
        bytes link_id;
    };
    struct get_vastlink_signed_keys_result {
        public_keys_set  signed_keys;
    };
    get_vastlink_signed_keys_result get_vastlink_signed_keys(const get_vastlink_signed_keys_params& params) const;

    struct get_script_params {
        script_name name;
    };
    fc::variant get_script(const get_script_params& params) const;

private:
    const controller& db_;
};

class read_write {};

}  // namespace vast_apis

class vast_plugin : public plugin<vast_plugin> {
public:
    APPBASE_PLUGIN_REQUIRES((chain_plugin))

    vast_plugin();
    virtual ~vast_plugin();

    virtual void set_program_options(options_description& cli, options_description& cfg) override;

    void plugin_initialize(const variables_map& options);
    void plugin_startup();
    void plugin_shutdown();

    vast_apis::read_only  get_read_only_api() const;
    vast_apis::read_write get_read_write_api();

private:
    std::unique_ptr<class vast_plugin_impl> my_;
};

}  // namespace vast

FC_REFLECT(vast::vast_apis::read_only::get_domain_params, (name));
FC_REFLECT(vast::vast_apis::read_only::get_group_params, (name));
FC_REFLECT(vast::vast_apis::read_only::get_token_params, (domain)(name));
FC_REFLECT(vast::vast_apis::read_only::get_tokens_params, (domain)(skip)(take));
FC_REFLECT(vast::vast_apis::read_only::get_fungible_params, (id));
FC_REFLECT(vast::vast_apis::read_only::get_fungible_balance_params, (address)(sym_id));
FC_REFLECT(vast::vast_apis::read_only::get_fungible_psvbonus_params, (id));
FC_REFLECT(vast::vast_apis::read_only::get_suspend_params, (name));
FC_REFLECT(vast::vast_apis::read_only::get_stakepool_params, (sym_id));
FC_REFLECT(vast::vast_apis::read_only::get_validator_params, (name));
FC_REFLECT(vast::vast_apis::read_only::get_staking_shares_params, (address));
FC_REFLECT(vast::vast_apis::read_only::get_vastlink_signed_keys_params, (link_id));
FC_REFLECT(vast::vast_apis::read_only::get_vastlink_signed_keys_result, (signed_keys));
FC_REFLECT(vast::vast_apis::read_only::get_script_params, (name));