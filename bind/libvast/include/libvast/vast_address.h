/**
 *  @file
 *  @copyright defined in vast/LICENSE.txt
 */
#pragma once
#include "vast.h"
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef vast_data_t vast_public_key_t;
typedef vast_data_t vast_address_t;

int vast_address_from_string(const char* str, vast_address_t** addr /* out */);
int vast_address_to_string(vast_address_t* addr, char** str /* out */);
int vast_address_public_key(vast_public_key_t *pub_key, vast_address_t** addr/* out */);
int vast_address_reserved(vast_address_t** addr/* out */);
int vast_address_generated(const char* prefix, const char* key, uint32_t nonce, vast_address_t** addr/* out */);
int vast_address_get_public_key(vast_address_t* addr, vast_public_key_t **pub_key/* out */);
int vast_address_get_prefix(vast_address_t* addr, char** str/* out */);
int vast_address_get_key(vast_address_t* addr, char** str/* out */);
int vast_address_get_nonce(vast_address_t* addr, uint32_t* nonce/* out */);
int vast_address_get_type(vast_address_t* addr, char** str/* out */);

#ifdef __cplusplus
} // extern "C"
#endif
