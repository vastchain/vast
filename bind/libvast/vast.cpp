#include <libvast/vast.h>
#include <string.h>
#include <stdlib.h>
#include <vast/chain/version.hpp>
#include <vast/chain/contracts/vast_contract_abi.hpp>

extern "C" {

int
vast_free(void* ptr) {
    if(ptr == nullptr) {
        return VAST_INVALID_ARGUMENT;
    }
    free(ptr);
    return VAST_OK;
}

int
vast_equals(vast_data_t* rhs, vast_data_t* lhs) {
    if(rhs == nullptr) {
        return VAST_INVALID_ARGUMENT;
    }
    if(lhs == nullptr) {
        return VAST_INVALID_ARGUMENT;
    }
    if(rhs->sz != lhs->sz) {
        return VAST_SIZE_NOT_EQUALS;
    }
    if(rhs->buf == lhs->buf) {
        return VAST_OK;
    }
    return memcmp(rhs->buf, lhs->buf, rhs->sz) == 0 ? VAST_OK : VAST_DATA_NOT_EQUALS;
}

int
vast_version() {
    auto ver = vast::chain::contracts::vast_contract_abi_version();
    return ver.get_version();
}

thread_local int last_error_code = 0;

int
vast_set_last_error(int code) {
    last_error_code = code;
    return code;
}

int
vast_last_error() {
    return last_error_code;
}

}  // extern "C"