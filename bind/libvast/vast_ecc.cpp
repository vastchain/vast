/**
 *  @file
 *  @copyright defined in vast/LICENSE.txt
 */

#include <libvast/vast_ecc.h>
#include "vast_impl.hpp"

#include <string.h>
#include <limits>
#include <fc/crypto/private_key.hpp>
#include <fc/crypto/public_key.hpp>
#include <fc/crypto/signature.hpp>
#include <fc/crypto/sha256.hpp>

using fc::sha256;
using fc::crypto::private_key;
using fc::crypto::public_key;
using fc::crypto::signature;

extern "C" {

int
vast_generate_new_pair(vast_public_key_t** pub_key /* out */, vast_private_key_t** priv_key /* out */) {
    if(pub_key == nullptr) {
        return VAST_INVALID_ARGUMENT;
    }
    if(priv_key == nullptr) {
        return VAST_INVALID_ARGUMENT;
    }

    try {
        auto pk  = private_key::generate();
        auto pub = pk.get_public_key();

        *pub_key  = get_vast_data(pub);
        *priv_key = get_vast_data(pk);
    }
    CATCH_AND_RETURN(VAST_INTERNAL_ERROR)

    return VAST_OK;
}

int
vast_get_public_key(vast_private_key_t* priv_key, vast_public_key_t** pub_key /* out */) {
    if(priv_key == nullptr) {
        return VAST_INVALID_ARGUMENT;
    }
    if(pub_key == nullptr) {
        return VAST_INVALID_ARGUMENT;
    }
    auto pk = private_key();
    if(extract_data(priv_key, pk) != VAST_OK) {
        return VAST_INVALID_PRIVATE_KEY;
    }
    try {
        auto pub = pk.get_public_key();
        *pub_key = get_vast_data(pub);
    }
    CATCH_AND_RETURN(VAST_INTERNAL_ERROR)

    return VAST_OK;
}

int
vast_sign_hash(vast_private_key_t* priv_key, vast_checksum_t* hash, vast_signature_t** sign /* out */) {
    if(priv_key == nullptr) {
        return VAST_INVALID_ARGUMENT;
    }
    if(hash == nullptr) {
        return VAST_INVALID_ARGUMENT;
    }
    if(sign == nullptr) {
        return VAST_INVALID_ARGUMENT;
    }
    auto pk = private_key();
    if(extract_data(priv_key, pk) != VAST_OK) {
        return VAST_INVALID_PRIVATE_KEY;
    }
    auto h = sha256();
    if(extract_data(hash, h) != VAST_OK) {
        return VAST_INVALID_SIGNATURE;
    }
    try {
        auto sig = pk.sign(h);
        *sign = get_vast_data(sig);
    }
    CATCH_AND_RETURN(VAST_INTERNAL_ERROR)

    return VAST_OK;
}

int
vast_recover(vast_signature_t* sign, vast_checksum_t* hash, vast_public_key_t** pub_key /* out */) {
    if(sign == nullptr) {
        return VAST_INVALID_ARGUMENT;
    }
    if(hash == nullptr) {
        return VAST_INVALID_ARGUMENT;
    }
    if(pub_key == nullptr) {
        return VAST_INVALID_ARGUMENT;
    }
    auto sig = signature();
    auto h = sha256();
    if(extract_data(sign, sig) != VAST_OK) {
        return VAST_INVALID_SIGNATURE;
    }
    if(extract_data(hash, h) != VAST_OK) {
        return VAST_INVALID_HASH;
    }
    try {
        auto pkey = public_key(sig, h);
        *pub_key = get_vast_data(pkey);
    }
    CATCH_AND_RETURN(VAST_INTERNAL_ERROR)

    return VAST_OK;
}

int
vast_hash(const char* buf, size_t sz, vast_checksum_t** hash /* out */) {
    if(buf == nullptr) {
        return VAST_INVALID_ARGUMENT;
    }
    if(sz == 0 || sz >= std::numeric_limits<uint32_t>::max()) {
        return VAST_INVALID_ARGUMENT;
    }
    if(hash == nullptr) {
        return VAST_INVALID_ARGUMENT;
    }
    try {
        auto h = sha256::hash(buf, sz);
        *hash = get_vast_data(h);
    }
    CATCH_AND_RETURN(VAST_INTERNAL_ERROR)

    return VAST_OK;
}

int
vast_public_key_string(vast_public_key_t* pub_key, char** str /* out */) {
    if(pub_key == nullptr) {
        return VAST_INVALID_ARGUMENT;
    }
    if(str == nullptr) {
        return VAST_INVALID_ARGUMENT;
    }
    auto pkey = public_key();
    if(extract_data(pub_key, pkey) != VAST_OK) {
        return VAST_INVALID_PUBLIC_KEY;
    }
    auto pkey_str = (std::string)pkey;
    *str = strdup(pkey_str);
    return VAST_OK;
}

int
vast_private_key_string(vast_private_key_t* priv_key, char** str /* out */) {
    if(priv_key == nullptr) {
        return VAST_INVALID_ARGUMENT;
    }
    if(str == nullptr) {
        return VAST_INVALID_ARGUMENT;
    }
    auto pkey = private_key();
    if(extract_data(priv_key, pkey) != VAST_OK) {
        return VAST_INVALID_PRIVATE_KEY;
    }
    auto pkey_str = (std::string)pkey;
    *str = strdup(pkey_str);
    return VAST_OK;
}

int
vast_signature_string(vast_signature_t* sign, char** str /* out */) {
    if(sign == nullptr) {
        return VAST_INVALID_ARGUMENT;
    }
    if(str == nullptr) {
        return VAST_INVALID_ARGUMENT;
    }
    auto sig = signature();
    if(extract_data(sign, sig) != VAST_OK) {
        return VAST_INVALID_SIGNATURE;
    }
    auto sign_str = (std::string)sig;
    *str = strdup(sign_str);
    return VAST_OK;
}

int
vast_checksum_string(vast_checksum_t* hash, char** str /* out */) {
    if(hash == nullptr) {
        return VAST_INVALID_ARGUMENT;
    }
    if(str == nullptr) {
        return VAST_INVALID_ARGUMENT;
    }
    auto h = sha256();
    if(extract_data(hash, h) != VAST_OK) {
        return VAST_INVALID_HASH;
    }
    auto hash_str = (std::string)h;
    *str = strdup(hash_str);
    return VAST_OK;
}

int
vast_public_key_from_string(const char* str, vast_public_key_t** pub_key /* out */) {
    if(str == nullptr) {
        return VAST_INVALID_ARGUMENT;
    }
    if(pub_key == nullptr) {
        return VAST_INVALID_ARGUMENT;
    }
    try {
        auto pkey = public_key(std::string(str));
        auto data = get_vast_data(pkey);
        *pub_key = data;
    }
    CATCH_AND_RETURN(VAST_INTERNAL_ERROR)

    return VAST_OK;
}

int
vast_private_key_from_string(const char* str, vast_private_key_t** priv_key /* out */) {
    if(str == nullptr) {
        return VAST_INVALID_ARGUMENT;
    }
    if(priv_key == nullptr) {
        return VAST_INVALID_ARGUMENT;
    }
    try {
        auto pkey = private_key(std::string(str));
        auto data = get_vast_data(pkey);
        *priv_key = data;
    }
    CATCH_AND_RETURN(VAST_INTERNAL_ERROR)

    return VAST_OK;
}

int
vast_signature_from_string(const char* str, vast_signature_t** sign /* out */) {
    if(str == nullptr) {
        return VAST_INVALID_ARGUMENT;
    }
    if(sign == nullptr) {
        return VAST_INVALID_ARGUMENT;
    }
    try {
        auto sig = signature(std::string(str));
        auto data = get_vast_data(sig);
        *sign = data;
    }
    CATCH_AND_RETURN(VAST_INTERNAL_ERROR)

    return VAST_OK;
}

int
vast_checksum_from_string(const char* str, vast_checksum_t** hash /* out */) {
    if(str == nullptr) {
        return VAST_INVALID_ARGUMENT;
    }
    if(hash == nullptr) {
        return VAST_INVALID_ARGUMENT;
    }
    try {
        auto h = sha256(std::string(str));
        auto data = get_vast_data(h);
        *hash = data;
    }
    CATCH_AND_RETURN(VAST_INTERNAL_ERROR)

    return VAST_OK;
}

} // extern "C"