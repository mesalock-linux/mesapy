from ffi import ffi
import __pypy__

@ffi.def_extern()
def say():
    print "Hello, World!"
    print "Welcome to MesaPy for SGX."
    print "Do what I mean:", __pypy__.do_what_I_mean()
