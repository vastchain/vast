/**
 *  @file
 *  @copyright defined in vast/LICENSE.txt
 */

#include <libvast/vast_address.h>
#include "vast_impl.hpp"

#include <string.h>
#include <stddef.h>
#include <vast/chain/name.hpp>
#include <vast/chain/address.hpp>
#include <fc/crypto/public_key.hpp>

using vast::chain::name;
using vast::chain::name128;
using vast::chain::address;
using fc::crypto::public_key;

extern "C" {

int
vast_address_from_string(const char* str, vast_address_t** addr /* out */) {
    if (str == nullptr) {
        return VAST_INVALID_ARGUMENT;
    }
    try {
        auto _addr = address(std::string(str));
        *addr = get_vast_data(_addr);
    }
    CATCH_AND_RETURN(VAST_INTERNAL_ERROR)
    
    return VAST_OK;
}

int
vast_address_to_string(vast_address_t* addr, char** str /* out */) {
    if (addr == nullptr) {
        return VAST_INVALID_ARGUMENT;
    }
    
    auto _addr = address();
    if(extract_data(addr, _addr) != VAST_OK) {
        return VAST_INVALID_ADDRESS;
    }
    try {
        auto out = _addr.to_string();
        *str = strdup(out);
    }
    CATCH_AND_RETURN(VAST_INTERNAL_ERROR)

    return VAST_OK;
}

int
vast_address_public_key(vast_public_key_t *pub_key, vast_address_t** addr/* out */) {
    if (pub_key == nullptr) {
        return VAST_INVALID_ARGUMENT;
    }
    auto pkey = public_key();
    if(extract_data(pub_key, pkey) != VAST_OK) {
        return VAST_INVALID_PUBLIC_KEY;
    }
    try {
        auto _addr = address(pkey);
        *addr = get_vast_data(_addr);
    }
    CATCH_AND_RETURN(VAST_INTERNAL_ERROR)

    return VAST_OK;
}

int
vast_address_reserved(vast_address_t** addr/* out */) {
    try {
        auto _addr = address();
        *addr = get_vast_data(_addr);
    }
    CATCH_AND_RETURN(VAST_INTERNAL_ERROR)

    return VAST_OK;
}

int
vast_address_generated(const char* prefix, const char* key, uint32_t nonce, vast_address_t** addr/* out */) {
    try {
        auto _prefix = name(prefix);
        auto _key = name128(key);
        auto _addr = address(_prefix, _key, nonce);
        *addr = get_vast_data(_addr);
    }
    CATCH_AND_RETURN(VAST_INTERNAL_ERROR)

    return VAST_OK;
}

int
vast_address_get_public_key(vast_address_t* addr, vast_public_key_t **pub_key/* out */) {
    if (addr == nullptr) {
        return VAST_INVALID_ARGUMENT;
    }

    auto _addr = address();
    if(extract_data(addr, _addr) != VAST_OK) {
        return VAST_INVALID_ADDRESS;
    }

    try {
        auto pkey = _addr.get_public_key();
        *pub_key = get_vast_data(pkey);
    }
    CATCH_AND_RETURN(VAST_INTERNAL_ERROR)

    return VAST_OK;
}

int
vast_address_get_prefix(vast_address_t* addr, char** str/* out */) {
    if (addr == nullptr) {
        return VAST_INVALID_ARGUMENT;
    }

    auto _addr = address();
    if(extract_data(addr, _addr) != VAST_OK) {
        return VAST_INVALID_ADDRESS;
    }

    try {
        auto prefix = _addr.get_prefix();
        *str = strdup(prefix.to_string());
    }
    CATCH_AND_RETURN(VAST_INTERNAL_ERROR)

    return VAST_OK;
}

int
vast_address_get_key(vast_address_t* addr, char** str/* out */) {
    if (addr == nullptr) {
        return VAST_INVALID_ARGUMENT;
    }

    auto _addr = address();
    if(extract_data(addr, _addr) != VAST_OK) {
        return VAST_INVALID_ADDRESS;
    }

    try {
        auto key = _addr.get_key();
        *str = strdup(key.to_string());
    }
    CATCH_AND_RETURN(VAST_INTERNAL_ERROR)

    return VAST_OK;
}

int
vast_address_get_nonce(vast_address_t* addr, uint32_t* nonce/* out */) {
    if (addr == nullptr) {
        return VAST_INVALID_ARGUMENT;
    }

    auto _addr = address();
    if(extract_data(addr, _addr) != VAST_OK) {
        return VAST_INVALID_ADDRESS;
    }

    try {
        auto out = _addr.get_nonce();
        *nonce = out;
    }
    CATCH_AND_RETURN(VAST_INTERNAL_ERROR)

    return VAST_OK;
}

int
vast_address_get_type(vast_address_t* addr, char** str/* out */) {
    if (addr == nullptr) {
        return VAST_INVALID_ARGUMENT;
    }

    auto _addr = address();
    if (extract_data(addr, _addr) != VAST_OK) {
        return VAST_INVALID_ADDRESS;
    }

    try {
        if (_addr.is_reserved()) {
            *str = strdup("reserved");
        }
        else if (_addr.is_public_key()) {
            *str = strdup("public_key");
        }
        else {
            *str = strdup("generated");
        }
    }
    CATCH_AND_RETURN(VAST_INTERNAL_ERROR)

    return VAST_OK;
}

}
