from ffi import ffi

@ffi.def_extern()
def python_exec(python_code):
    exec(ffi.string(python_code))
