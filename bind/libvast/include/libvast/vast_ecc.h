/**
 *  @file
 *  @copyright defined in vast/LICENSE.txt
 */
#pragma once
#include "vast.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef vast_data_t vast_public_key_t;
typedef vast_data_t vast_private_key_t;
typedef vast_data_t vast_signature_t;
typedef vast_data_t vast_checksum_t;

int vast_generate_new_pair(vast_public_key_t** pub_key /* out */, vast_private_key_t** priv_key /* out */);
int vast_get_public_key(vast_private_key_t* priv_key, vast_public_key_t** pub_key /* out */);
int vast_sign_hash(vast_private_key_t* priv_key, vast_checksum_t* hash, vast_signature_t** sign /* out */);
int vast_recover(vast_signature_t* sign, vast_checksum_t* hash, vast_public_key_t** pub_key /* out */);
int vast_hash(const char* buf, size_t sz, vast_checksum_t** hash /* out */);

int vast_public_key_string(vast_public_key_t* pub_key, char** str /* out */);
int vast_private_key_string(vast_private_key_t* priv_key, char** str /* out */);
int vast_signature_string(vast_signature_t* sign, char** str /* out */);
int vast_checksum_string(vast_checksum_t* hash, char** str /* out */);

int vast_public_key_from_string(const char* str, vast_public_key_t** pub_key /* out */);
int vast_private_key_from_string(const char* str, vast_private_key_t** priv_key /* out */);
int vast_signature_from_string(const char* str, vast_signature_t** sign /* out */);
int vast_checksum_from_string(const char* str, vast_checksum_t** hash /* out */);

#ifdef __cplusplus
} // extern "C"
#endif
