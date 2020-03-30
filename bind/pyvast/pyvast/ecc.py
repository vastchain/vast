from . import vast_exception, libvast
from .vast_data import VastData


class PublicKey(VastData):
    def __init__(self, data):
        super().__init__(data)

    def __str__(self):
        return self.to_string()

    def to_string(self):
        str_c = self.vast.ffi.new('char**')
        ret = self.vast.lib.vast_public_key_string(self.data, str_c)
        vast_exception.vast_exception_raiser(ret)
        str = self.vast.ffi.string(str_c[0]).decode('utf-8')
        ret = self.vast.lib.vast_free(str_c[0])
        vast_exception.vast_exception_raiser(ret)
        return str

    @staticmethod
    def from_string(str):
        vast = libvast.check_lib_init()
        public_key_c = vast.ffi.new('vast_public_key_t**')
        str_c = bytes(str, encoding='utf-8')
        ret = vast.lib.vast_public_key_from_string(str_c, public_key_c)
        vast_exception.vast_exception_raiser(ret)
        return PublicKey(public_key_c[0])

    @staticmethod
    def recover(sign, hash):
        vast = libvast.check_lib_init()
        public_key_c = vast.ffi.new('vast_public_key_t**')
        ret = vast.lib.vast_recover(sign.data, hash.data, public_key_c)
        vast_exception.vast_exception_raiser(ret)
        return PublicKey(public_key_c[0])


class PrivateKey(VastData):
    def __init__(self, data):
        super().__init__(data)

    def __str__(self):
        return self.to_string()

    def to_string(self):
        str_c = self.vast.ffi.new('char**')
        ret = self.vast.lib.vast_private_key_string(self.data, str_c)
        vast_exception.vast_exception_raiser(ret)
        str = self.vast.ffi.string(str_c[0]).decode('utf-8')
        ret = self.vast.lib.vast_free(str_c[0])
        vast_exception.vast_exception_raiser(ret)
        return str

    def get_public_key(self):
        public_key_c = self.vast.ffi.new('vast_public_key_t**')
        ret = self.vast.lib.vast_get_public_key(self.data, public_key_c)
        vast_exception.vast_exception_raiser(ret)
        return PublicKey(public_key_c[0])

    def sign_hash(self, hash):
        signature_c = self.vast.ffi.new('vast_signature_t**')
        ret = self.vast.lib.vast_sign_hash(
            self.data, hash.data, signature_c)
        vast_exception.vast_exception_raiser(ret)
        return Signature(signature_c[0])

    @staticmethod
    def from_string(str):
        vast = libvast.check_lib_init()
        private_key_c = vast.ffi.new('vast_private_key_t**')
        str_c = bytes(str, encoding='utf-8')
        ret = vast.lib.vast_private_key_from_string(
            str_c, private_key_c)
        vast_exception.vast_exception_raiser(ret)
        return PrivateKey(private_key_c[0])


class Signature(VastData):
    def __init__(self, data):
        super().__init__(data)

    def __str__(self):
        return self.to_string()

    def to_string(self):
        str_c = self.vast.ffi.new('char**')
        ret = self.vast.lib.vast_signature_string(self.data, str_c)
        vast_exception.vast_exception_raiser(ret)
        str = self.vast.ffi.string(str_c[0]).decode('utf-8')
        ret = self.vast.lib.vast_free(str_c[0])
        vast_exception.vast_exception_raiser(ret)
        return str


class Checksum(VastData):
    def __init__(self, data):
        super().__init__(data)

    def __str__(self):
        return self.to_string()

    def to_string(self):
        str_c = self.vast.ffi.new('char**')
        ret = self.vast.lib.vast_checksum_string(self.data, str_c)
        vast_exception.vast_exception_raiser(ret)
        str = self.vast.ffi.string(str_c[0]).decode('utf-8')
        ret = self.vast.lib.vast_free(str_c[0])
        vast_exception.vast_exception_raiser(ret)
        return str

    @staticmethod
    def from_string(str):
        vast = libvast.check_lib_init()
        str_c = bytes(str, encoding='utf-8')
        vast_hash = vast.ffi.new('vast_checksum_t**')
        ret = vast.lib.vast_hash(str_c, len(str_c), vast_hash)
        vast_exception.vast_exception_raiser(ret)
        return Checksum(vast_hash[0])


def generate_new_pair():
    vast = libvast.check_lib_init()
    public_key_c = vast.ffi.new('vast_public_key_t**')
    private_key_c = vast.ffi.new('vast_private_key_t**')
    ret = vast.lib.vast_generate_new_pair(public_key_c, private_key_c)
    vast_exception.vast_exception_raiser(ret)
    return PublicKey(public_key_c[0]), PrivateKey(private_key_c[0])
