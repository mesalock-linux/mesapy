from testexec_library import ffi, lib

@ffi.def_extern()
def testexec(string):
    a =ffi.string(string) 
    exec(a)
