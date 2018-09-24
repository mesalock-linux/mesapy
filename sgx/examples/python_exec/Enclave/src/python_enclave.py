import sgx_cffi
import _cffi_backend as backend

ffi = sgx_cffi.FFI(backend)

ffi.embedding_api("void python_exec(char *python_code);")
ffi.embedding_init_code(
"""
from python_enclave import ffi

@ffi.def_extern()
def python_exec(python_code):
    exec(ffi.string(python_code))
"""
)
ffi.set_source("python_enclave", "")
ffi.emit_c_code("python_enclave.c")
