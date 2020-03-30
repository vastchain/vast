/**
 *  @file
 *  @copyright defined in vast/LICENSE.txt
 */
#pragma once

#include <vast/chain/types.hpp>

namespace vast { namespace chain {

/**
 *  For each action dispatched this receipt is generated
 */
struct action_receipt {
    digest_type act_digest;
    uint64_t    global_sequence = 0;  ///< total number of actions dispatched since genesis

    digest_type digest() const { return digest_type::hash(*this); }
};

}}  // namespace vast::chain

FC_REFLECT(vast::chain::action_receipt, (act_digest)(global_sequence));
