import cffi
ffi = cffi.FFI()

ffi.embedding_api(open("apicm.h").read())
ffi.embedding_init_code(open("implcm.py").read())

ffi.set_source("cm_library", "")
ffi.compile(verbose=True)
