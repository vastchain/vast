/**
 *  @file
 *  @copyright defined in vast/LICENSE.txt
 */
#include <vast/chain/chain_id_type.hpp>

#include <fc/variant.hpp>
#include <vast/chain/exceptions.hpp>

namespace vast { namespace chain {

void
chain_id_type::reflector_init() const {
    VAST_ASSERT(*reinterpret_cast<const fc::sha256*>(this) != fc::sha256(), chain_id_type_exception, "chain_id_type cannot be zero");
}

}}  // namespace vast::chain

namespace fc {

void
to_variant(const vast::chain::chain_id_type& cid, fc::variant& v) {
    to_variant(static_cast<const fc::sha256&>(cid), v);
}

void
from_variant(const fc::variant& v, vast::chain::chain_id_type& cid) {
    from_variant(v, static_cast<fc::sha256&>(cid));
}

}  // namespace fc