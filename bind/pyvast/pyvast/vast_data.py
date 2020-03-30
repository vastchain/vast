from io import StringIO

from . import vast_exception, libvast


class VastData:
    def __init__(self, data):
        self.data = data
        self.vast = libvast.check_lib_init()

    def __del__(self):
        ret = self.vast.lib.vast_free(self.data)
        vast_exception.vast_exception_raiser(ret)

    def to_hex_string(self):
        hstr = StringIO()
        for i in range(self.data.sz):
            hstr.write(self.data.buf[i].hex())
        return hstr.getvalue()
