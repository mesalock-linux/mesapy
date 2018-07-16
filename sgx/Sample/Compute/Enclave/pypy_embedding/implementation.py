from cm_library import ffi, lib

@ffi.def_extern()
def compute_num(first, second):
    """ Compute the absolute distance between two numbers. """
    ret = first - second
    return ret
