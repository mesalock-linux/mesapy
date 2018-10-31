from ffi import ffi

@ffi.def_extern()
def test_math():
    t = AppTestMath()
    for k, v in AppTestMath.__dict__.items():
        if k.startswith("test_"):
            print "[+] testing", k
            v(t)

class AppTestMath:
    def test_factorial(self):
        import math
        assert math.factorial(0) == 1
        assert math.factorial(1) == 1
        assert math.factorial(2) == 2
        assert math.factorial(5) == 120
        assert math.factorial(5.) == 120
        raises(ValueError, math.factorial, -1)
        raises(ValueError, math.factorial, -1.)
        raises(ValueError, math.factorial, 1.1)

    def test_log1p(self):
        import math
        self.ftest(math.log1p(1/math.e-1), -1)
        self.ftest(math.log1p(0), 0)
        self.ftest(math.log1p(math.e-1), 1)
        self.ftest(math.log1p(1), math.log(2))

    def test_acosh(self):
        import math
        self.ftest(math.acosh(1), 0)
        self.ftest(math.acosh(2), 1.3169578969248168)
        assert math.isinf(math.asinh(float("inf")))
        raises(ValueError, math.acosh, 0)

    def test_asinh(self):
        import math
        self.ftest(math.asinh(0), 0)
        self.ftest(math.asinh(1), 0.88137358701954305)
        self.ftest(math.asinh(-1), -0.88137358701954305)
        assert math.isinf(math.asinh(float("inf")))

    def test_atanh(self):
        import math
        self.ftest(math.atanh(0), 0)
        self.ftest(math.atanh(0.5), 0.54930614433405489)
        self.ftest(math.atanh(-0.5), -0.54930614433405489)
        raises(ValueError, math.atanh, 1.)
        assert math.isnan(math.atanh(float("nan")))

    def test_trunc(self):
        import math
        assert math.trunc(1.9) == 1.0
        raises((AttributeError, TypeError), math.trunc, 1.9j)
        class foo(object):
            def __trunc__(self):
                return "truncated"
        assert math.trunc(foo()) == "truncated"

    def test_erf(self):
        import math
        assert math.erf(100.0) == 1.0
        assert math.erf(-1000.0) == -1.0
        assert math.erf(float("inf")) == 1.0
        assert math.erf(float("-inf")) == -1.0
        assert math.isnan(math.erf(float("nan")))
        # proper tests are in rpython/rlib/test/test_rfloat
        assert round(math.erf(1.0), 9) == 0.842700793

    def test_erfc(self):
        import math
        assert math.erfc(0.0) == 1.0
        assert math.erfc(-0.0) == 1.0
        assert math.erfc(float("inf")) == 0.0
        assert math.erfc(float("-inf")) == 2.0
        assert math.isnan(math.erf(float("nan")))
        assert math.erfc(1e-308) == 1.0

    def test_gamma(self):
        import math
        assert raises(ValueError, math.gamma, 0.0)
        assert math.gamma(5.0) == 24.0
        assert math.gamma(6.0) == 120.0
        assert raises(ValueError, math.gamma, -1)
        assert math.gamma(0.5) == math.pi ** 0.5

    def test_lgamma(self):
        import math
        math.lgamma(1.0) == 0.0
        math.lgamma(2.0) == 0.0
        # proper tests are in rpython/rlib/test/test_rfloat
        assert round(math.lgamma(5.0), 9) == round(math.log(24.0), 9)
        assert round(math.lgamma(6.0), 9) == round(math.log(120.0), 9)
        assert raises(ValueError, math.gamma, -1)
        assert round(math.lgamma(0.5), 9) == round(math.log(math.pi ** 0.5), 9)

    def ftest(self, actual, expected):
        assert abs(actual - expected) < 10E-5

def raises(expected_exception, *args, **kwargs):
    func = args[0]
    try:
        func(*args[1:], **kwargs)
    except expected_exception:
        return True
    message = "DID NOT RAISE {}".format(expected_exception)
    print message
    assert False, message
