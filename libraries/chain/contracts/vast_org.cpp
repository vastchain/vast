/**
 *  @file
 *  @copyright defined in vast/LICENSE.txt
 */
#include <vast/chain/contracts/vast_org.hpp>
#include <vast/chain/token_database.hpp>
#include <vast/chain/genesis_state.hpp>

namespace vast { namespace chain { namespace contracts {

void
initialize_vast_org(token_database& tokendb, const genesis_state& genesis) {
    // Add reserved VastChain foundation group
    if(!tokendb.exists_token(token_type::group, std::nullopt, N128(.VastChain))) {
        auto v = make_db_value(genesis.vast_org);
        tokendb.put_token(token_type::group, action_op::add, std::nullopt, N128(.VastChain), v.as_string_view());
    }

    // Add reserved VAST & PVAST fungible tokens
    if(!tokendb.exists_token(token_type::fungible, std::nullopt, VAST_SYM_ID)) {
        assert(!tokendb.exists_token(token_type::fungible, std::nullopt, PVAST_SYM_ID));

        auto v = make_db_value(genesis.get_vast_ft());
        tokendb.put_token(token_type::fungible, action_op::add, std::nullopt, VAST_SYM_ID, v.as_string_view());

        auto v2 = make_db_value(genesis.get_pvast_ft());
        tokendb.put_token(token_type::fungible, action_op::add, std::nullopt, PVAST_SYM_ID, v2.as_string_view());

        auto addr = address(N(.fungible), name128::from_number(VAST_SYM_ID), 0);
        auto prop = property_stakes(property {
                        .amount = genesis.vast.total_supply.amount(),
                        .frozen_amount = 0,
                        .sym = vast_sym(),
                        .created_at = genesis.initial_timestamp.sec_since_epoch(),
                        .created_index = 0
                    });
        auto v3 = make_db_value(prop);
        tokendb.put_asset(addr, VAST_SYM_ID, v3.as_string_view());
    }
}

void
update_vast_org(token_database& tokendb, const genesis_state& genesis) {
    auto s = tokendb.new_savepoint_session();

    auto v = make_db_value(genesis.get_vast_ft());
    tokendb.put_token(token_type::fungible, action_op::update, std::nullopt, VAST_SYM_ID, v.as_string_view());

    auto v2 = make_db_value(genesis.get_pvast_ft());
    tokendb.put_token(token_type::fungible, action_op::update, std::nullopt, PVAST_SYM_ID, v2.as_string_view());
}

}}}  // namespace vast::chain::contracts
