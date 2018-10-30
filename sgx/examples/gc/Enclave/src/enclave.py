from ffi import ffi
import gc

@ffi.def_extern()
def gc_example():
    for i in range(1024):
        x = [0] * 1024

    gc.collect()

    for i in range(1024):
        x = [0] * 1024
