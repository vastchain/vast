/**
 *  @file
 *  @copyright defined in vast/LICENSE.txt
 */
#pragma once
#include "vast.h"
#include <stdint.h>
#include <vast/chain/contracts/vast_link.hpp>

#ifdef __cplusplus
extern "C" {
#endif

typedef void vast_link_t;
typedef vast_data_t vast_signature_t;
typedef vast_data_t vast_private_key_t;

vast_link_t* vast_link_new();
void vast_link_free(vast_link_t*);
int vast_link_tostring(vast_link_t*, char**);
int vast_link_parse_from_vastli(const char*, vast_link_t*);
int vast_link_get_header(vast_link_t*, uint16_t*);
int vast_link_set_header(vast_link_t*, uint16_t);
int vast_link_get_segment_int(vast_link_t*, uint8_t, uint32_t*);
int vast_link_get_segment_str(vast_link_t*, uint8_t, char**);
int vast_link_add_segment_int(vast_link_t*, uint8_t, uint32_t);
int vast_link_add_segment_str(vast_link_t*, uint8_t, const char*);
int vast_link_get_signatures(vast_link_t*, vast_signature_t***, uint32_t*);
int vast_link_sign(vast_link_t*, vast_private_key_t*);

#ifdef __cplusplus
} // extern "C"
#endif
