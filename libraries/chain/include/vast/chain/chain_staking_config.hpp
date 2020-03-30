/**
 *  @file
 *  @copyright defined in vast/LICENSE.txt
 */
#pragma once
#include <vast/chain/config.hpp>
#include <vast/chain/types.hpp>

namespace vast { namespace chain {

struct chain_staking_config {
    int32_t unstake_pending_days = config::default_unstake_pending_days;
    int32_t cycles_per_period    = config::default_cycles_per_period;
    int32_t blocks_per_cycle     = config::default_blocks_per_cycle;
    int32_t staking_threshold    = config::default_staking_threshold;
};

}}  // namespace vast::chain

FC_REFLECT(vast::chain::chain_staking_config, (unstake_pending_days)(cycles_per_period)(blocks_per_cycle)(staking_threshold));
