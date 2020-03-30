/**
 *  @file
 *  @copyright defined in vast/LICENSE.txt
 */

#include <vast/chain/chain_config.hpp>
#include <vast/chain/exceptions.hpp>

namespace vast { namespace chain {

void 
chain_config::validate()const {
    VAST_ASSERT(1 <= max_authority_depth, action_exception,
              "max authority depth should be at least 1");
}

}}  // namespace vast::chain