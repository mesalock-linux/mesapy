import cffi
ffi = cffi.FFI()

ffi.embedding_api(open("apihw.h").read())
ffi.embedding_init_code(open("implhw.py").read())

ffi.set_source("hw_library", "")
ffi.compile(verbose=True)
