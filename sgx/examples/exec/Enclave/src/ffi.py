import sgx_cffi
import _cffi_backend as backend

ffi = sgx_cffi.FFI(backend)

ffi.embedding_api("""
    int64_t mesapy_exec(const char *py_script,
                        int py_argc,
                        char *py_argv[],
                        char *py_ret, uint64_t py_ret_man_len);
""")
with open("enclave.py") as f:
    ffi.embedding_init_code(f.read())
ffi.set_source("ffi", "")
ffi.emit_c_code("ffi.c")
