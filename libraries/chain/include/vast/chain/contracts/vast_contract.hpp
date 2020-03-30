/**
 *  @file
 *  @copyright defined in vast/LICENSE.txt
 */
#pragma once

namespace vast { namespace chain { namespace contracts {

template<uint64_t>
struct apply_action {};

}}}  // namespace vast::chain::contracts

#include <vast/chain/contracts/vast_contract_common.hpp>
#include <vast/chain/contracts/vast_contract_metas.hpp>
#include <vast/chain/contracts/vast_contract_nft.hpp>
#include <vast/chain/contracts/vast_contract_ft.hpp>
#include <vast/chain/contracts/vast_contract_group.hpp>
#include <vast/chain/contracts/vast_contract_lock.hpp>
#include <vast/chain/contracts/vast_contract_suspend.hpp>
#include <vast/chain/contracts/vast_contract_bonus.hpp>
#include <vast/chain/contracts/vast_contract_vastlink.hpp>
#include <vast/chain/contracts/vast_contract_utils.hpp>
#include <vast/chain/contracts/vast_contract_staking.hpp>
