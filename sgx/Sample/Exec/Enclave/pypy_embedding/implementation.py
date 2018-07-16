from exec_library import ffi, lib

@ffi.def_extern()
def exect(string):
    a =ffi.string(string)
    exec(a)
