from . import libvast


class VASTErrCode:
    VAST_OK = 0
    VAST_INTERNAL_ERROR = -1
    VAST_INVALID_ARGUMENT = -2
    VAST_INVALID_PRIVATE_KEY = -3
    VAST_INVALID_PUBLIC_KEY = -4
    VAST_INVALID_SIGNATURE = -5
    VAST_INVALID_HASH = -6
    VAST_INVALID_ACTION = -7
    VAST_INVALID_BINARY = -8
    VAST_INVALID_JSON = -9
    VAST_INVALID_ADDRESS = -10
    VAST_SIZE_NOT_EQUALS = -11
    VAST_DATA_NOT_EQUALS = -12
    VAST_INVALID_LINK = -13
    VAST_NOT_INIT = -15


class VASTException(Exception):
    def __init__(self, err):
        if err == 'VAST_INTERNAL_ERROR':
            vast = libvast.check_lib_init()
            code = vast.vast_last_error()

            errmsg = '{}: {}'.format(err, code)
            super().__init__(self, errmsg)
        else:
            super().__init__(self, err)


class VASTInternalErrorException(Exception):
    def __init__(self):
        err = 'VAST_INTERNAL_ERROR'
        super().__init__(self, err)


class VASTInvalidArgumentException(Exception):
    def __init__(self):
        err = 'VAST_INVALID_ARGUMENT'
        super().__init__(self, err)


class VASTInvalidPrivateKeyException(Exception):
    def __init__(self):
        err = 'VAST_INVALID_PRIVATE_KEY'
        super().__init__(self, err)


class VASTInvalidPublicKeyException(Exception):
    def __init__(self):
        err = 'VAST_INVALID_PUBLIC_KEY'
        super().__init__(self, err)


class VASTInvalidSignatureException(Exception):
    def __init__(self):
        err = 'VAST_INVALID_SIGNATURE'
        super().__init__(self, err)


class VASTInvalidHashException(Exception):
    def __init__(self):
        err = 'VAST_INVALID_HASH'
        super().__init__(self, err)


class VASTInvalidActionException(Exception):
    def __init__(self):
        err = 'VAST_INVALID_ACTION'
        super().__init__(self, err)


class VASTInvalidBinaryException(Exception):
    def __init__(self):
        err = 'VAST_INVALID_BINARY'
        super().__init__(self, err)


class VASTInvalidJsonException(Exception):
    def __init__(self):
        err = 'VAST_INVALID_JSON'
        super().__init__(self, err)


class VASTInvalidAddressException(Exception):
    def __init__(self):
        err = 'VAST_INVALID_ADDRESS'
        super().__init__(self, err)


class VASTSizeNotEqualsException(Exception):
    def __init__(self):
        err = 'VAST_SIZE_NOT_EQUALS'
        super().__init__(self, err)


class VASTDataNotEqualsException(Exception):
    def __init__(self):
        err = 'VAST_DATA_NOT_EQUALS'
        super().__init__(self, err)


class VASTInvalidLinkException(Exception):
    def __init__(self):
        err = 'VAST_INVALID_LINK'
        super().__init__(self, err)


class VASTNotInitException(Exception):
    def __init__(self):
        err = 'VAST_NOT_INIT'
        super().__init__(self, err)


ex_map = {
    VASTErrCode.VAST_INTERNAL_ERROR: VASTInternalErrorException,
    VASTErrCode.VAST_INVALID_ARGUMENT: VASTInvalidArgumentException,
    VASTErrCode.VAST_INVALID_PRIVATE_KEY: VASTInvalidPrivateKeyException,
    VASTErrCode.VAST_INVALID_PUBLIC_KEY: VASTInvalidPublicKeyException,
    VASTErrCode.VAST_INVALID_SIGNATURE: VASTInvalidSignatureException,
    VASTErrCode.VAST_INVALID_HASH: VASTInvalidHashException,
    VASTErrCode.VAST_INVALID_ACTION: VASTInvalidActionException,
    VASTErrCode.VAST_INVALID_BINARY: VASTInvalidBinaryException,
    VASTErrCode.VAST_INVALID_JSON: VASTInvalidJsonException,
    VASTErrCode.VAST_INVALID_ADDRESS: VASTInvalidAddressException,
    VASTErrCode.VAST_INVALID_LINK: VASTInvalidLinkException,
    VASTErrCode.VAST_SIZE_NOT_EQUALS: VASTSizeNotEqualsException,
    VASTErrCode.VAST_DATA_NOT_EQUALS: VASTDataNotEqualsException,
    VASTErrCode.VAST_NOT_INIT: VASTNotInitException
}


def vast_exception_raiser(error_code):
    if error_code == VASTErrCode.VAST_OK:
        return
    if error_code in ex_map:
        raise ex_map[error_code]
    raise Exception('Unknown error code')
