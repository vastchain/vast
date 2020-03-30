/**
 *  @file
 *  @copyright defined in vast/LICENSE.txt
 */

#include <libvast/vast_vastlink.h>
#include "vast_impl.hpp"

#include <string.h>
#include <stddef.h>
#include <vast/chain/contracts/vast_link.hpp>
#include <fc/crypto/private_key.hpp>

using vast::chain::contracts::vast_link;
using fc::crypto::private_key;

extern "C" {

vast_link_t*
vast_link_new() {
    auto linkp = new vast_link();
    return (vast_link_t*)linkp;
}

void
vast_link_free(vast_link_t* linkp) {
    delete (vast_link*)(linkp);
}

int
vast_link_tostring(vast_link_t* linkp, char** str) {
    if (linkp == nullptr) {
        return VAST_INVALID_ARGUMENT;
    }
    try {
        auto _str = ((vast_link*)(linkp))->to_string();
        *str = strdup(_str);
    }
    CATCH_AND_RETURN(VAST_INTERNAL_ERROR)
    return VAST_OK;
}

int
vast_link_parse_from_vastli(const char* str, vast_link_t* linkp) {
    if (str == nullptr) {
        return VAST_INVALID_ARGUMENT;
    }
    try {
        *((vast_link*)(linkp)) = vast_link::parse_from_vastli(std::string(str));
    }
    CATCH_AND_RETURN(VAST_INTERNAL_ERROR)
    return VAST_OK;
}

int
vast_link_get_header(vast_link_t* linkp, uint16_t* header/* out */) {
    if (linkp == nullptr) {
        return VAST_INVALID_ARGUMENT;
    }
    try {
        *header = ((vast_link*)(linkp))->get_header();
    }
    CATCH_AND_RETURN(VAST_INTERNAL_ERROR)
    return VAST_OK;
}

int
vast_link_set_header(vast_link_t* linkp, uint16_t header) {
    if (linkp == nullptr) {
        return VAST_INVALID_ARGUMENT;
    }
    try {
        ((vast_link*)(linkp))->set_header(header);
    }
    CATCH_AND_RETURN(VAST_INTERNAL_ERROR)
    return VAST_OK;
}

int
vast_link_get_segment_int(vast_link_t* linkp, uint8_t key, uint32_t* intv) {
    if (linkp == nullptr) {
        return VAST_INVALID_ARGUMENT;
    }
    try {
        auto _segment = ((vast_link*)(linkp))->get_segment(key);
        if(_segment.intv) {
            *intv = *_segment.intv;
        }
        else {
            return VAST_INVALID_ARGUMENT;
        }
    }
    CATCH_AND_RETURN(VAST_INTERNAL_ERROR)
    return VAST_OK;
}

int
vast_link_get_segment_str(vast_link_t* linkp, uint8_t key, char** strv) {
    if (linkp == nullptr) {
        return VAST_INVALID_ARGUMENT;
    }
    try {
        auto _segment = ((vast_link*)(linkp))->get_segment(key);
        if(_segment.strv) {
            *strv = strdup(*_segment.strv);
        }
        else {
            return VAST_INVALID_ARGUMENT;
        }
    }
    CATCH_AND_RETURN(VAST_INTERNAL_ERROR)
    return VAST_OK;
}

int
vast_link_add_segment_int(vast_link_t* linkp, uint8_t key, uint32_t intv) {
    if (linkp == nullptr) {
        return VAST_INVALID_ARGUMENT;
    }
    try {
        auto _segment = vast_link::segment(key, intv);
        ((vast_link*)(linkp))->add_segment(_segment);
    }
    CATCH_AND_RETURN(VAST_INTERNAL_ERROR)
    return VAST_OK;
}

int
vast_link_add_segment_str(vast_link_t* linkp, uint8_t key, const char* strv) {
    if (linkp == nullptr) {
        return VAST_INVALID_ARGUMENT;
    }
    try {
        auto _segment = vast_link::segment(key, std::string(strv));
        ((vast_link*)(linkp))->add_segment(_segment);
    }
    CATCH_AND_RETURN(VAST_INTERNAL_ERROR)
    return VAST_OK;
}

int
vast_link_clear_signatures(vast_link_t* linkp) {
    if (linkp == nullptr) {
        return VAST_INVALID_ARGUMENT;
    }
    try {
        ((vast_link*)(linkp))->clear_signatures();
    }
    CATCH_AND_RETURN(VAST_INTERNAL_ERROR)
    return VAST_OK;
}

int
vast_link_get_signatures(vast_link_t* linkp, vast_signature_t*** signs, uint32_t* len) {
    if (linkp == nullptr) {
        return VAST_INVALID_ARGUMENT;
    }
    try {
        auto _signs = ((vast_link*)(linkp))->get_signatures();
        auto size   = _signs.size();
        auto psigns = (vast_signature_t**)malloc(sizeof(vast_signature_t*) * size);

        int i = 0;
        for(auto it = _signs.begin(); it != _signs.end(); it++, i++) {
            psigns[i] = get_vast_data(*it);
        }
        
        *signs = psigns;
        *len   = size;
    }
    CATCH_AND_RETURN(VAST_INTERNAL_ERROR)
    return VAST_OK;
}

int
vast_link_sign(vast_link_t* linkp, vast_private_key_t* priv_key) {
    if (linkp == nullptr) {
        return VAST_INVALID_ARGUMENT;
    }
    auto pk = private_key();
    if (extract_data(priv_key, pk) != VAST_OK) {
        return VAST_INVALID_PRIVATE_KEY;
    }
    try {
        ((vast_link*)(linkp))->sign(pk);
    }
    CATCH_AND_RETURN(VAST_INTERNAL_ERROR)
    return VAST_OK;
}

}
