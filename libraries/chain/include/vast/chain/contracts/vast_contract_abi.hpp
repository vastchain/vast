/**
 *  @file
 *  @copyright defined in vast/LICENSE.txt
 */
#pragma once

namespace vast { namespace chain {
class version;
}}  // namespace vast::chain

namespace vast { namespace chain { namespace contracts {

struct abi_def;

abi_def vast_contract_abi();
version vast_contract_abi_version();

}}}  // namespace vast::chain::contracts
