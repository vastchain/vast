import os
import sys

from cffi import FFI

from . import vast_exception


class LibVAST:
    ffi = FFI()
    lib = None
    abi = None


def check_lib_init():
    if LibVAST.lib is None:
        vast_exception.vast_exception_raiser(
            vast_exception.VASTErrCode.VAST_NOT_INIT)
    return LibVAST


def init_vast_lib():
    assert LibVAST.abi is None

    LibVAST.ffi.cdef("""
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
            int vast_last_error();


            typedef vast_data_t vast_bin_t;
            typedef vast_data_t vast_chain_id_t;
            typedef vast_data_t vast_block_id_t;
            typedef vast_data_t vast_public_key_t;
            typedef vast_data_t vast_private_key_t;
            typedef vast_data_t vast_signature_t;
            typedef vast_data_t vast_checksum_t;
            typedef vast_data_t vast_address_t;
            typedef void       vast_link_t;


            void* vast_abi();
            void vast_free_abi(void* abi);
            int vast_abi_json_to_bin(void* vast_abi, const char* action, const char* json, vast_bin_t** bin /* out */);
            int vast_abi_bin_to_json(void* vast_abi, const char* action, vast_bin_t* bin, char** json /* out */);
            int vast_trx_json_to_digest(void* vast_abi, const char* json, vast_chain_id_t* chain_id, vast_checksum_t** digest /* out */);
            int vast_chain_id_from_string(const char* str, vast_chain_id_t** chain_id /* out */);


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

            int vast_block_id_from_string(const char* str, vast_block_id_t** block_id /* out */);
            int vast_ref_block_num(vast_block_id_t* block_id, uint16_t* ref_block_num);
            int vast_ref_block_prefix(vast_block_id_t* block_id, uint32_t* ref_block_prefix);
            
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
            """)

    if sys.platform == 'linux':
        ext = '.so'
    elif sys.platform == 'darwin':
        ext = '.dylib'
    else:
        raise Exception('Not supported platform: {}'.format(sys.platform))

    if 'LIBVAST_PATH' in os.environ:
        LibVAST.lib = LibVAST.ffi.dlopen(
            os.environ['LIBVAST_PATH'] + '/libvast' + ext)
    else:
        LibVAST.lib = LibVAST.ffi.dlopen('libvast' + ext)

    LibVAST.abi = LibVAST.lib.vast_abi()


def init_lib():
    LibVAST.ffi.init_once(init_vast_lib, 'init_vast')
    return LibVAST.lib.vast_version()
