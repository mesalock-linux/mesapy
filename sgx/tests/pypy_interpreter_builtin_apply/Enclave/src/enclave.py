from ffi import ffi

@ffi.def_extern()
def test_builtin_apply():
    t = AppTestApply()
    for k, v in AppTestApply.__dict__.items():
        if k.startswith("test_"):
            print "[+] testing", k
            v(t)

class AppTestApply:

    def test_trivial_listonly(self):
        def mymin(*args):
            return min(list(args))

        assert apply(mymin, [-1,-2,-3,-4]) == -4

    def test_trivial_dictonly(self):
        def mymin(*arr, **kwargs):
            return min(list(arr) + kwargs.values())
        assert apply(mymin,
                               [], {'null' : 0, 'one': 1, 'two' : 2}) == (
                               0)
    def test_trivial(self):
        def mymin(*arr, **kwargs):
            return min(list(arr) + kwargs.values())
        assert apply(mymin,
                               [-1,-2,-3,-4],
                               {'null' : 0, 'one': 1, 'two' : 2}) == (
                               (-4))

def raises(expected_exception, *args, **kwargs):
    func = args[0]
    try:
        func(*args[1:], **kwargs)
    except expected_exception:
        return True
    message = "DID NOT RAISE {}".format(expected_exception)
    print message
    assert False, message
