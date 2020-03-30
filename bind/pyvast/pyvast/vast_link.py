import random
from enum import Enum, IntFlag

from . import vast_exception, libvast
from .ecc import Signature
from .vast_data import VastData


class HeaderType(IntFlag):
    version1  = 1
    everiPass = 2
    everiPay  = 4
    destroy   = 8


class SegmentType(Enum):
    timestamp = 42
    max_pay = 43
    symbol_id = 44
    domain = 91
    token = 92
    max_pay_str = 94
    address = 95
    link_id = 156


class VastLink():
    def __init__(self):
        self.vast = libvast.check_lib_init()
        self.linkp = self.vast.lib.vast_link_new()

    def __del__(self):
        self.free()

    def free(self):
        self.vast.lib.vast_link_free(self.linkp)

    def __str__(self):
        return self.to_string()

    def to_string(self):
        strv_c = self.vast.ffi.new('char**')
        ret = self.vast.lib.vast_link_tostring(self.linkp, strv_c)
        vast_exception.vast_exception_raiser(ret)
        strv = self.vast.ffi.string(strv_c[0]).decode('utf-8')
        ret = self.vast.lib.vast_free(strv_c[0])
        vast_exception.vast_exception_raiser(ret)
        return strv

    @staticmethod
    def parse_from_vastli(link_str):
        vast_link = VastLink()
        str_c = bytes(link_str, encoding='utf-8')
        ret = vast_link.vast.lib.vast_link_parse_from_vastli(str_c, vast_link.linkp)
        vast_exception.vast_exception_raiser(ret)
        return vast_link

    def get_header(self):
        header_c = self.vast.ffi.new('uint16_t*')
        ret = self.vast.lib.vast_link_get_header(self.linkp, header_c)
        vast_exception.vast_exception_raiser(ret)
        return int(header_c[0])

    def set_header(self, header):
        ret = self.vast.lib.vast_link_set_header(self.linkp, header)
        vast_exception.vast_exception_raiser(ret)

    def get_segment_str(self, type_str):
        strv_c = self.vast.ffi.new('char**')
        ret = self.vast.lib.vast_link_get_segment_str(
            self.linkp, SegmentType[type_str].value, strv_c)
        vast_exception.vast_exception_raiser(ret)
        if type_str == 'link_id':
            strv = self.vast.ffi.buffer(strv_c[0], 16)[:]
        else:
            strv = self.vast.ffi.string(strv_c[0]).decode('utf-8')
        ret = self.vast.lib.vast_free(strv_c[0])
        vast_exception.vast_exception_raiser(ret)
        return strv

    def get_segment_int(self, type_str):
        intv_c = self.vast.ffi.new('uint32_t*')
        ret = self.vast.lib.vast_link_get_segment_int(
            self.linkp, SegmentType[type_str].value, intv_c)
        vast_exception.vast_exception_raiser(ret)
        return int(intv_c[0])

    def add_segment_str(self, type_str, strv):
        if type_str == 'link_id':
            strv_c = strv
        else:
            strv_c = bytes(strv, encoding='utf-8')
        ret = self.vast.lib.vast_link_add_segment_str(
            self.linkp, SegmentType[type_str].value, strv_c)
        vast_exception.vast_exception_raiser(ret)

    def add_segment_int(self, type_str, intv):
        ret = self.vast.lib.vast_link_add_segment_int(
            self.linkp, SegmentType[type_str].value, intv)
        vast_exception.vast_exception_raiser(ret)

    def get_signatures(self):
        signs_c = self.vast.ffi.new('vast_signature_t***')
        len_c = self.vast.ffi.new('uint32_t*')
        ret = self.vast.lib.vast_link_get_signatures(self.linkp, signs_c, len_c)
        vast_exception.vast_exception_raiser(ret)
        l = [Signature(signs_c[0][i]) for i in range(int(len_c[0]))]
        ret = self.vast.lib.vast_free(signs_c[0])
        vast_exception.vast_exception_raiser(ret)
        return l

    def sign(self, priv_key):
        ret = self.vast.lib.vast_link_sign(self.linkp, priv_key.data)
        vast_exception.vast_exception_raiser(ret)

    def set_timestamp(self, timestamp):
        self.add_segment_int('timestamp', timestamp)

    def set_max_pay(self, max_pay):
        self.add_segment_int('max_pay', max_pay)

    def set_symbol_id(self, symbol_id):
        self.add_segment_int('symbol_id', symbol_id)

    def set_domain(self, domain):
        self.add_segment_str('domain', domain)

    def set_token(self, token):
        self.add_segment_str('token', token)

    def set_max_pay_str(self, max_pay_str):
        self.add_segment_str('max_pay_str', max_pay_str)

    def set_address(self, address):
        self.add_segment_str('address', address)

    def get_timestamp(self):
        return self.get_segment_int('timestamp')

    def get_max_pay(self):
        return self.get_segment_int('max_pay')

    def get_symbol_id(self):
        return self.get_segment_int('symbol_id')

    def get_domain(self):
        return self.get_segment_str('domain')

    def get_token(self):
        return self.get_segment_str('token')

    def get_max_pay_str(self):
        return self.get_segment_str('max_pay_str')

    def get_address(self):
        return self.get_segment_str('address')

    def set_link_id(self, link_id):
        self.add_segment_str('link_id', link_id)

    def set_link_id_rand(self):
        l = [random.randint(1, 255) for _ in range(16)]
        self.set_link_id(bytes(l))

    def get_link_id(self):
        return self.get_segment_str('link_id')
