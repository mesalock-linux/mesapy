from hw_library import ffi, lib

@ffi.def_extern()
def my_helloworld():
    print ("helloworld. this line will be printed!")
