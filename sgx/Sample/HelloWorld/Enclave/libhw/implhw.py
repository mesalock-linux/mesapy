from hw_library import ffi, lib

@ffi.def_extern()
def my_helloworld():
    """ Compute the absolute distance between two numbers. """
    print ("helloworld. this line will be printed!")
