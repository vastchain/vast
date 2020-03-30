from . import vast_exception, libvast
from .vast_data import VastData


def version():
    return libvast.init_lib()


def json_to_bin(action, json):
    vast = libvast.check_lib_init()
    action_c = bytes(action, encoding='utf-8')
    json_c = bytes(json, encoding='utf-8')
    bin_c = vast.ffi.new('vast_bin_t**')
    ret = vast.lib.vast_abi_json_to_bin(
        vast.abi, action_c, json_c, bin_c)
    vast_exception.vast_exception_raiser(ret)
    return VastData(bin_c[0])


def bin_to_json(action, bin):
    vast = libvast.check_lib_init()
    action_c = bytes(action, encoding='utf-8')
    bin_c = bin.data
    json_c = vast.ffi.new('char** ')
    ret = vast.lib.vast_abi_bin_to_json(
        vast.abi, action_c, bin_c, json_c)
    vast_exception.vast_exception_raiser(ret)
    json = vast.ffi.string(json_c[0]).decode('utf-8')
    ret = vast.lib.vast_free(json_c[0])
    vast_exception.vast_exception_raiser(ret)
    return json


def trx_json_to_digest(json, chain_id):
    vast = libvast.check_lib_init()
    json_c = bytes(json, encoding='utf-8')
    chain_id_c = chain_id.data
    digest_c = vast.ffi.new('vast_checksum_t**')
    ret = vast.lib.vast_trx_json_to_digest(
        vast.abi, json_c, chain_id_c, digest_c)
    vast_exception.vast_exception_raiser(ret)
    return VastData(digest_c[0])


class ChainId(VastData):
    def __init__(self, data):
        super().__init__(data)

    @staticmethod
    def from_string(str):
        vast = libvast.check_lib_init()
        str_c = bytes(str, encoding='utf-8')
        chain_id_c = vast.ffi.new('vast_chain_id_t**')
        ret = vast.lib.vast_chain_id_from_string(str_c, chain_id_c)
        vast_exception.vast_exception_raiser(ret)
        return ChainId(chain_id_c[0])


class BlockId(VastData):
    def __init__(self, data):
        super().__init__(data)

    @staticmethod
    def from_string(str):
        vast = libvast.check_lib_init()
        str_c = bytes(str, encoding='utf-8')
        block_id_c = vast.ffi.new('vast_block_id_t**')
        ret = vast.lib.vast_block_id_from_string(str_c, block_id_c)
        vast_exception.vast_exception_raiser(ret)
        return BlockId(block_id_c[0])

    def ref_block_num(self):
        uint16_c = self.vast.ffi.new('uint16_t*')
        ret = self.vast.lib.vast_ref_block_num(self.data, uint16_c)
        vast_exception.vast_exception_raiser(ret)
        return int(uint16_c[0])

    def ref_block_prefix(self):
        uint32_c = self.vast.ffi.new('uint32_t*')
        ret = self.vast.lib.vast_ref_block_prefix(self.data, uint32_c)
        vast_exception.vast_exception_raiser(ret)
        return int(uint32_c[0])
