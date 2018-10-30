from ffi import ffi
import math, cmath

@ffi.def_extern()
def math_example():
    print math.factorial(0)
    print math.acosh(2)
    print math.log1p(1/math.e-1)
    print math.atanh(-0.5)

    assert cmath.sqrt(3+4j) == 2+1j
    z = cmath.rect(2.0, cmath.pi/2)
    assert abs(z - 2j) < 1e-10
    print z
