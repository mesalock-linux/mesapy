from ffi import ffi

@ffi.def_extern()
def test_raise():
    t = AppTestRaise()
    for k, v in AppTestRaise.__dict__.items():
        if k.startswith("test_"):
            print "[+] testing", k
            v(t)

class AppTestRaise:
    def test_arg_as_string(self):
        def f():
            raise "test"
        raises(TypeError, f)

    def test_control_flow(self):
        try:
            raise Exception
            raise AssertionError, "exception failed to raise"
        except:
            pass
        else:
            raise AssertionError, "exception executing else clause!"

    def test_1arg(self):
        try:
            raise SystemError, 1
        except Exception as e:
            assert e.args[0] == 1

    def test_2args(self):
        try:
            raise SystemError, (1, 2)
        except Exception as e:
            assert e.args[0] == 1
            assert e.args[1] == 2

def raises(expected_exception, *args, **kwargs):
    func = args[0]
    try:
        func(*args[1:], **kwargs)
    except expected_exception:
        return True
    message = "DID NOT RAISE {}".format(expected_exception)
    print message
    assert False, message
