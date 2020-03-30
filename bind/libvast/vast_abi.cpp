/**
 *  @file
 *  @copyright defined in vast/LICENSE.txt
 */
#include "libvast/vast_abi.h"
#include "vast_impl.hpp"

#include <fc/crypto/sha256.hpp>
#include <fc/bitutil.hpp>
#include <fc/variant.hpp>
#include <fc/io/json.hpp>

#include <vast/chain/execution_context_mock.hpp>
#include <vast/chain/contracts/vast_contract_abi.hpp>
#include <vast/chain/contracts/abi_serializer.hpp>
#include <vast/chain/types.hpp>

using fc::sha256;
using vast::chain::bytes;
using vast::chain::chain_id_type;
using vast::chain::vast_execution_context_mock;
using vast::chain::transaction;
using vast::chain::contracts::abi_serializer;
using vast::chain::contracts::abi_def;

template <> 
vast_data_t*
get_vast_data<bytes>(const bytes& b) {
    auto sz = sizeof(vast_data_t) + b.size();
    auto data = (vast_data_t*)malloc(sz);
    data->sz = b.size(); 
    memcpy((char*)data + sizeof(vast_data_t), b.data(), b.size());
    return data; 
} 
 
template <> 
int 
extract_data<bytes>(vast_data_t* data, bytes& val) {
    if(data->sz == 0) { 
        return VAST_INVALID_ARGUMENT;
    } 
    val.resize(data->sz); 
    memcpy(&val[0], data->buf, data->sz); 
    return VAST_OK;
} 

struct abi_context {
    std::unique_ptr<abi_serializer>             abi;
    std::unique_ptr<vast_execution_context_mock> exec_ctx;
};

extern "C" {

void*
vast_abi() {
    auto abic      = new abi_context();
    abic->abi      = std::make_unique<abi_serializer>(vast::chain::contracts::vast_contract_abi(), std::chrono::hours(1));
    abic->exec_ctx = std::make_unique<vast_execution_context_mock>();

    return (void*)abic;
}

void
vast_free_abi(void* abi) {
    delete (abi_context*)abi;
}

int
vast_abi_json_to_bin(void* vast_abi, const char* action, const char* json, vast_bin_t** bin /* out */) {
    if(vast_abi == nullptr) {
        return VAST_INVALID_ARGUMENT;
    }
    if(action == nullptr) {
        return VAST_INVALID_ARGUMENT;
    }
    if(json == nullptr) {
        return VAST_INVALID_ARGUMENT;
    }
    if(bin == nullptr) {
        return VAST_INVALID_ARGUMENT;
    }
    auto& abic = *(abi_context*)vast_abi;
    auto  var  = fc::variant();
    try {
        var = fc::json::from_string(json);
        if(!var.is_object()) {
            return VAST_INVALID_JSON;
        }
    }
    CATCH_AND_RETURN(VAST_INVALID_JSON)

    auto type = abic.exec_ctx->get_acttype_name(action);
    if(type.empty()) {
        return VAST_INVALID_ACTION;
    }
    try {
        auto b = abic.abi->variant_to_binary(type, var, *abic.exec_ctx);
        if(b.empty()) {
            return VAST_INVALID_JSON;
        }
        auto data = get_vast_data(b);
        *bin = data;
    }
    CATCH_AND_RETURN(VAST_INTERNAL_ERROR)
    
    return VAST_OK;
}

int
vast_abi_bin_to_json(void* vast_abi, const char* action, vast_bin_t* bin, char** json /* out */) {
    if(vast_abi == nullptr) {
        return VAST_INVALID_ARGUMENT;
    }
    if(action == nullptr) {
        return VAST_INVALID_ARGUMENT;
    }
    if(bin == nullptr) {
        return VAST_INVALID_ARGUMENT;
    }
    if(json == nullptr) {
        return VAST_INVALID_ARGUMENT;
    }
    auto& abic = *(abi_context*)vast_abi;
    auto  type = abic.exec_ctx->get_acttype_name(action);
    if(type.empty()) {
        return VAST_INVALID_ACTION;
    }
    try {
        bytes b;
        if(extract_data(bin, b) != VAST_OK) {
            return VAST_INVALID_BINARY;
        }
        auto var = abic.abi->binary_to_variant(type, b, *abic.exec_ctx);
        auto str = fc::json::to_string(var);
        *json = strdup(str);
    }
    CATCH_AND_RETURN(VAST_INTERNAL_ERROR)

    return VAST_OK;
}

int
vast_trx_json_to_digest(void* vast_abi, const char* json,  vast_chain_id_t* chain_id, vast_checksum_t** digest /* out */) {
    if(vast_abi == nullptr) {
        return VAST_INVALID_ARGUMENT;
    }
    if(json == nullptr) {
        return VAST_INVALID_ARGUMENT;
    }
    if(digest == nullptr) {
        return VAST_INVALID_ARGUMENT;
    }
    sha256 idhash;
    if(extract_data(chain_id, idhash) != VAST_OK) {
        return VAST_INVALID_HASH;
    }

    auto& abic = *(abi_context*)vast_abi;
    auto  trx  = transaction();
    try {
        auto var = fc::json::from_string(json);
        abic.abi->from_variant(var, trx, *abic.exec_ctx);

        auto d  = trx.sig_digest(chain_id_type(idhash));
        *digest = get_vast_data(d);
    }
    CATCH_AND_RETURN(VAST_INTERNAL_ERROR)

    return VAST_OK;
}

int
vast_chain_id_from_string(const char* str, vast_chain_id_t** chain_id /* out */) {
    return vast_checksum_from_string(str, chain_id);
}

int
vast_block_id_from_string(const char* str, vast_block_id_t** block_id /* out */) {
    return vast_checksum_from_string(str, block_id);
}

int
vast_ref_block_num(vast_block_id_t* block_id, uint16_t* ref_block_num) {
    if(block_id == nullptr) {
        return VAST_INVALID_ARGUMENT;
    }
    sha256 idhash;
    if(extract_data(block_id, idhash) != VAST_OK) {
        return VAST_INVALID_HASH;
    }
    *ref_block_num = (uint16_t)fc::endian_reverse_u32(idhash._hash[0]);
    return VAST_OK;
}

int
vast_ref_block_prefix(vast_block_id_t* block_id, uint32_t* ref_block_prefix) {
    if(block_id == nullptr) {
        return VAST_INVALID_ARGUMENT;
    }
    sha256 idhash;
    if(extract_data(block_id, idhash) != VAST_OK) {
        return VAST_INVALID_HASH;
    }
    *ref_block_prefix = (uint32_t)idhash._hash[1];
    return VAST_OK;
}

}  // extern "C"