import sgx_cffi
import _cffi_backend as backend

ffi = sgx_cffi.FFI(backend)

ffi.embedding_api("void exec_example(char *python_code);")
ffi.embedding_api("int64_t mesapy_exec(const char *python_code, char *output, uint64_t buflen);")
with open("enclave.py") as f:
    ffi.embedding_init_code(f.read())
ffi.set_source("ffi", "")
ffi.emit_c_code("ffi.c")
