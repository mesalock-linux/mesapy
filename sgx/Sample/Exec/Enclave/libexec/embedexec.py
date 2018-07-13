import cffi
ffi = cffi.FFI()

ffi.embedding_api(open("apiexec.h").read())
ffi.embedding_init_code(open("implexec.py").read())

ffi.set_source("exec_library", "")
ffi.compile(verbose=True)



