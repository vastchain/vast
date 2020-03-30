/**
 *  @file
 *  @copyright defined in vast/LICENSE.txt
 */
#pragma once
#include <stdint.h>
#include "vast.h"
#include "vast_ecc.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef vast_data_t vast_bin_t;
typedef vast_data_t vast_chain_id_t;
typedef vast_data_t vast_block_id_t;

void* vast_abi();
void  vast_free_abi(void* abi);

int vast_abi_json_to_bin(void* vast_abi, const char* action, const char* json, vast_bin_t** bin /* out */);
int vast_abi_bin_to_json(void* vast_abi, const char* action, vast_bin_t* bin, char** json /* out */);
int vast_trx_json_to_digest(void* vast_abi, const char* json, vast_chain_id_t* chain_id, vast_checksum_t** digest /* out */);
int vast_chain_id_from_string(const char* str, vast_chain_id_t** chain_id /* out */);
int vast_block_id_from_string(const char* str, vast_block_id_t** block_id /* out */);
int vast_ref_block_num(vast_block_id_t* block_id, uint16_t* ref_block_num);
int vast_ref_block_prefix(vast_block_id_t* block_id, uint32_t* ref_block_prefix);

#ifdef __cplusplus
} // extern "C"
#endif
