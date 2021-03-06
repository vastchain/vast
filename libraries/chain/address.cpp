/**
 *  @file
 *  @copyright defined in vast/LICENSE.txt
 */
#include <vast/chain/address.hpp>
#include <vast/chain/exceptions.hpp>
#include <fc/crypto/base58.hpp>
#include <fc/crypto/ripemd160.hpp>
#include <fc/io/datastream.hpp>

namespace vast { namespace chain {

const std::string reserved_key = "VAST00000000000000000000000000000000000000000000000000";

namespace internal {

struct gen_wrapper {
public:
    uint32_t  checksum;
    uint32_t  nonce;
    uint64_t  prefix;
    uint128_t key;

public:
    uint32_t
    calculate_checksum() {
         auto encoder = fc::ripemd160::encoder();
         encoder.write((const char*)&prefix, sizeof(prefix));
         encoder.write((const char*)&key, sizeof(key));
         encoder.write((const char*)&nonce, sizeof(nonce));

         checksum = encoder.result()._hash[0];
         return checksum;
    }
} __attribute__((packed));

}  // namespace internal

void
address::to_bytes(char* buf, size_t sz) const {
    assert(sz == get_bytes_size());
    memcpy(buf, cache_.data(), cache_.size());
}

std::string
address::to_string() const {
    using namespace internal;

    switch(type()) {
    case reserved_t: {
        return reserved_key;
    }
    case public_key_t: {
        return (std::string)this->get_public_key();
    }
    case generated_t: {
        auto str = std::string();
        str.reserve(54);

        str.append("VAST0");

        auto gen = gen_wrapper();
        gen.prefix = this->get_prefix().value;
        gen.key = this->get_key().value;
        gen.nonce = this->get_nonce();
        gen.checksum = gen.calculate_checksum();

        auto hash = fc::to_base58((char*)&gen, sizeof(gen));
        VAST_ASSERT(hash.size() <= 54 - 4, address_type_exception, "Invalid generated values for address");

        str.append(54 - 4 - hash.size(), '0');
        str.append(std::move(hash));

        return str;
    }
    default: {
        VAST_ASSERT(false, address_type_exception, "Not valid address type: ${type}", ("type",type()));
    }
    }  // switch
}

address
address::from_string(const std::string& str) {
    using namespace internal;
    VAST_ASSERT(str.size() == 54, address_type_exception, "Address is not valid");

    address addr;
    // fast path
    if(str[4] != '0') {
        return address((public_key_type)str);
    }

    if(str == reserved_key) {
        return address();
    }

    auto gen = gen_wrapper();
    auto hash = str.substr(str.find_first_not_of('0', 5));
    fc::from_base58(hash, (char*)&gen, sizeof(gen));

    VAST_ASSERT(gen.checksum == gen.calculate_checksum(), address_type_exception, "Checksum doesn't match");
    return address(gen.prefix, gen.key, gen.nonce);
}

void
address::init_cache() const {  
    switch(this->type()) {
    case reserved_t: {
        memset(cache_.data(), 0, get_bytes_size());
        break;
    }
    case public_key_t: {
        memcpy(cache_.data(), &this->get_public_key(), sizeof(public_key_type::storage_type::type_at<0>));
        break;
    }
    case generated_t: {
        memset(cache_.data(), 0, get_bytes_size());

        auto ds = fc::datastream<char*>(cache_.data(), get_bytes_size());
        fc::raw::pack(ds, get_prefix());
        fc::raw::pack(ds, get_key());
        fc::raw::pack(ds, get_nonce());
        break;
    }
    }  // switch
}

}}  // namespace vast::chain

namespace fc {

void
to_variant(const vast::chain::address& addr, fc::variant& v) {
    v = addr.to_string();
}

void
from_variant(const fc::variant& v, vast::chain::address& addr) {
    addr = vast::chain::address::from_string(v.get_string());
}

}  // namespace fc