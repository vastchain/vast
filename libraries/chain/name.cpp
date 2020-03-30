/**
 *  @file
 *  @copyright defined in vast/LICENSE.txt
 */
#include <boost/algorithm/string.hpp>
#include <vast/chain/exceptions.hpp>
#include <vast/chain/name.hpp>
#include <fc/exception/exception.hpp>
#include <fc/variant.hpp>

namespace vast { namespace chain {

void
name::set(const char* str) {
    const auto len = strnlen(str, 14);
    VAST_ASSERT(len <= 13, name_type_exception, "Name is longer than 13 characters (${name}) ", ("name", string(str)));
    VAST_ASSERT(len > 0, name_type_exception, "Name cannot be empty");
    value = string_to_name(str);
    VAST_ASSERT(to_string() == string(str), name_type_exception,
               "Name not properly normalized (name: ${name}, normalized: ${normalized}) ",
               ("name", string(str))("normalized", to_string()));
}

name::operator string() const {
    static const char* charmap = ".abcdefghijklmnopqrstuvwxyz12345";

    string str(13, '.');

    auto tmp = value;
    str[12] = charmap[tmp & 0x0f];
    tmp >>= 4;

    for(auto i = 1u; i <= 12; ++i, tmp >>= 5) {
        char c    = charmap[tmp & 0x1f];
        str[12-i] = c;
    }

    str.erase(str.find_last_not_of('.') + 1);
    return str;
}

}}  // namespace vast::chain

namespace fc {

void
to_variant(const vast::chain::name& name, fc::variant& v) {
    v = std::string(name);
}

void
from_variant(const fc::variant& v, vast::chain::name& name) {
    name = v.get_string();
}

}  // namespace fc
