import sgx_cffi
import _cffi_backend as backend

ffi = sgx_cffi.FFI(backend)

ffi.embedding_api("void say();")
ffi.embedding_init_code(
"""
from python_enclave import ffi
import __pypy__

@ffi.def_extern()
def say():
    print "Hello, World!"
    print "Welcome to MesaPy for SGX."
    print "Do what I mean:", __pypy__.do_what_I_mean()
"""
)
ffi.set_source("python_enclave", "")
ffi.emit_c_code("python_enclave.c")
