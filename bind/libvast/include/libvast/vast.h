/**
 *  @file
 *  @copyright defined in vast/LICENSE.txt
 */
#pragma once
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    size_t  sz;
    char    buf[0];
} vast_data_t;

#define VAST_OK                       0
#define VAST_INTERNAL_ERROR          -1
#define VAST_INVALID_ARGUMENT        -2
#define VAST_INVALID_PRIVATE_KEY     -3
#define VAST_INVALID_PUBLIC_KEY      -4
#define VAST_INVALID_SIGNATURE       -5
#define VAST_INVALID_HASH            -6
#define VAST_INVALID_ACTION          -7
#define VAST_INVALID_BINARY          -8
#define VAST_INVALID_JSON            -9
#define VAST_INVALID_ADDRESS         -10
#define VAST_SIZE_NOT_EQUALS         -11
#define VAST_DATA_NOT_EQUALS         -12
#define VAST_INVALID_LINK            -13

int vast_free(void*);
int vast_equals(vast_data_t* rhs, vast_data_t* lhs);
int vast_version();
int vast_set_last_error(int code);
int vast_last_error();

#ifdef __cplusplus
} // extern "C"
#endif
