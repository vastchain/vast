/**
 *  @file
 *  @copyright defined in vast/LICENSE.txt
 */
#include <vast/chain/block_state.hpp>
#include <vast/chain/exceptions.hpp>

namespace vast { namespace chain {

block_state::block_state(const block_header_state& prev, block_timestamp_type when)
    : block_header_state(prev.generate_next(when))
    , block(std::make_shared<signed_block>()) {
    static_cast<block_header&>(*block) = header;
}

block_state::block_state(const block_header_state& prev, signed_block_ptr b, bool skip_validate_signee)
    : block_header_state(prev.next(*b, skip_validate_signee))
    , block(move(b)) {}

}}  // namespace vast::chain
