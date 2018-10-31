from ffi import ffi

@ffi.def_extern()
def exec_example(python_code):
    exec(ffi.string(python_code))
