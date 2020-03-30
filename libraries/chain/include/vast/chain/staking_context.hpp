/**
 *  @file
 *  @copyright defined in vast/LICENSE.txt
*/
#pragma once
#include <chainbase/chainbase.hpp>
#include <vast/chain/config.hpp>
#include <vast/chain/types.hpp>

namespace vast { namespace chain {

struct validator_context {
    account_name name;
};

class staking_context {
public:
    uint32_t period_version   = 0;  ///< sequentially incrementing version number
    uint32_t period_start_num = 0;
};

}}  // namespace vast::chain

FC_REFLECT(vast::chain::staking_context, (period_version)(period_start_num));
