from ffi import ffi

@ffi.def_extern()
def test_math():
    test_factorial()

def test_factorial():
    import math
    assert math.factorial(0) == 1
    assert math.factorial(1) == 1
    assert math.factorial(2) == 2
    assert math.factorial(5) == 120
    assert math.factorial(5.) == 120

    try: math.factorial(-1)
    except ValueError: pass
    else: assert False
