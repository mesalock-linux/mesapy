import cffi
ffi = cffi.FFI()

ffi.embedding_api(open("api.h").read())
ffi.embedding_init_code(open("implementation.py").read())

ffi.set_source("hw_library", "")
ffi.compile(verbose=True)
