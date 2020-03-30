/**
 *  @file
 *  @copyright defined in vast/LICENSE.txt
 */
#pragma once
#include <fc/io/raw.hpp>
#include <vast/chain/types.hpp>

namespace vast { namespace chain { namespace contracts {

struct vast_link_object {
    link_id_type        link_id;
    uint32_t            block_num;
    transaction_id_type trx_id;
};

}}}  // namespace vast::chain::contracts

FC_REFLECT(vast::chain::contracts::vast_link_object, (block_num)(link_id)(trx_id));
