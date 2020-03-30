from . import vast_exception, libvast
from .ecc import PublicKey
from .vast_data import VastData


class Address(VastData):
    def __init__(self, data):
        super().__init__(data)

    def __str__(self):
        return self.to_string()

    def to_string(self):
        str_c = self.vast.ffi.new('char**')
        ret = self.vast.lib.vast_address_to_string(self.data, str_c)
        vast_exception.vast_exception_raiser(ret)
        str = self.vast.ffi.string(str_c[0]).decode('utf-8')
        ret = self.vast.lib.vast_free(str_c[0])
        vast_exception.vast_exception_raiser(ret)
        return str

    @staticmethod
    def from_string(str):
        vast = libvast.check_lib_init()
        addr_c = vast.ffi.new('vast_address_t**')
        str_c = bytes(str, encoding='utf-8')
        ret = vast.lib.vast_address_from_string(str_c, addr_c)
        vast_exception.vast_exception_raiser(ret)
        return Address(addr_c[0])

    @staticmethod
    def public_key(pub_key):
        vast = libvast.check_lib_init()
        addr_c = vast.ffi.new('vast_address_t**')
        ret = vast.lib.vast_address_public_key(pub_key.data, addr_c)
        vast_exception.vast_exception_raiser(ret)
        return Address(addr_c[0])

    @staticmethod
    def reserved():
        vast = libvast.check_lib_init()
        addr_c = vast.ffi.new('vast_address_t**')
        ret = vast.lib.vast_address_reserved(addr_c)
        vast_exception.vast_exception_raiser(ret)
        return Address(addr_c[0])

    @staticmethod
    def generated(prefix, key, nonce):
        vast = libvast.check_lib_init()
        addr_c = vast.ffi.new('vast_address_t**')
        prefix_c = bytes(prefix, encoding='utf-8')
        key_c = bytes(key, encoding='utf-8')
        ret = vast.lib.vast_address_generated(prefix_c, key_c, nonce, addr_c)
        vast_exception.vast_exception_raiser(ret)
        return Address(addr_c[0])

    def get_public_key(self):
        pub_key_c = self.vast.ffi.new('vast_public_key_t**')
        ret = self.vast.lib.vast_address_get_public_key(self.data, pub_key_c)
        vast_exception.vast_exception_raiser(ret)
        return PublicKey(pub_key_c[0])

    def get_prefix(self):
        str_c = self.vast.ffi.new('char**')
        ret = self.vast.lib.vast_address_get_prefix(self.data, str_c)
        vast_exception.vast_exception_raiser(ret)
        str = self.vast.ffi.string(str_c[0]).decode('utf-8')
        ret = self.vast.lib.vast_free(str_c[0])
        vast_exception.vast_exception_raiser(ret)
        return str

    def get_key(self):
        str_c = self.vast.ffi.new('char**')
        ret = self.vast.lib.vast_address_get_key(self.data, str_c)
        vast_exception.vast_exception_raiser(ret)
        str = self.vast.ffi.string(str_c[0]).decode('utf-8')
        ret = self.vast.lib.vast_free(str_c[0])
        vast_exception.vast_exception_raiser(ret)
        return str

    def get_nonce(self):
        nonce_c = self.vast.ffi.new('uint32_t*')
        ret = self.vast.lib.vast_address_get_nonce(self.data, nonce_c)
        vast_exception.vast_exception_raiser(ret)
        return int(nonce_c[0])

    def get_type(self):
        str_c = self.vast.ffi.new('char**')
        ret = self.vast.lib.vast_address_get_type(self.data, str_c)
        vast_exception.vast_exception_raiser(ret)
        str = self.vast.ffi.string(str_c[0]).decode('utf-8')
        ret = self.vast.lib.vast_free(str_c[0])
        vast_exception.vast_exception_raiser(ret)
        return str
