from ffi import ffi
from array import array

@ffi.def_extern()
def test_array():
    t = AppTestArray()
    for k, v in AppTestArray.__dict__.items():
        if k.startswith("test_"):
            print "[+] testing", k
            v(t)

class AppTestArray(object):

    def test_ctor(self):
        assert len(array('c')) == 0
        assert len(array('i')) == 0

        raises(TypeError, array, 'hi')
        raises(TypeError, array, 1)
        raises(ValueError, array, 'q')

        a = array('c')
        raises(TypeError, a.append, 7)
        raises(TypeError, a.append, 'hi')
        a.append('h')
        assert a[0] == 'h'
        assert type(a[0]) is str
        assert len(a) == 1

        a = array('u')
        raises(TypeError, a.append, 7)
        raises(TypeError, a.append, u'hi')
        a.append(u'h')
        assert a[0] == u'h'
        assert type(a[0]) is unicode
        assert len(a) == 1

        a = array('c', ('a', 'b', 'c'))
        assert a[0] == 'a'
        assert a[1] == 'b'
        assert a[2] == 'c'
        assert len(a) == 3

        b = array('c', a)
        assert len(b) == 3
        assert a == b
        raises(TypeError, array, 'i', a)

        a = array('i', (1, 2, 3))
        b = array('h', (1, 2, 3))
        assert a == b

        for tc in 'bhilBHILfd':
            assert array(tc).typecode == tc
            raises(TypeError, array, tc, None)

        a = array('i', (1, 2, 3))
        b = array('h', a)
        assert list(b) == [1, 2, 3]

    def test_value_range(self):
        import sys
        values = (-129, 128, -128, 127, 0, 255, -1, 256,
                  -32768, 32767, -32769, 32768, 65535, 65536,
                  -2147483647, -2147483648, 2147483647, 4294967295, 4294967296,
                  )
        for bb in (8, 16, 32, 64, 128, 256, 512, 1024):
            for b in (bb - 1, bb, bb + 1):
                values += (2 ** b, 2 ** b + 1, 2 ** b - 1,
                           -2 ** b, -2 ** b + 1, -2 ** b - 1)

        for tc, ok, pt in (('b', (  -128,    34,   127),  int),
                           ('B', (     0,    23,   255),  int),
                           ('h', (-32768, 30535, 32767),  int),
                           ('H', (     0, 56783, 65535),  int),
                           ('i', (-32768, 30535, 32767),  int),
                           ('I', (     0, 56783, 65535), long),
                           ('l', (-2 ** 32 // 2, 34, 2 ** 32 // 2 - 1),  int),
                           ('L', (0, 3523532, 2 ** 32 - 1), long),
                           ):
            a = array(tc, ok)
            assert len(a) == len(ok)
            for v in ok:
                a.append(v)
            for i, v in enumerate(ok * 2):
                assert a[i] == v
                assert type(a[i]) is pt or (
                    # A special case: we return ints in Array('I') on 64-bits,
                    # whereas CPython returns longs.  The difference is
                    # probably acceptable.
                    tc == 'I' and
                    sys.maxint > 2147483647 and type(a[i]) is int)
            for v in ok:
                a[1] = v
                assert a[0] == ok[0]
                assert a[1] == v
                assert a[2] == ok[2]
            assert len(a) == 2 * len(ok)
            for v in values:
                try:
                    a[1] = v
                    assert a[0] == ok[0]
                    assert a[1] == v
                    assert a[2] == ok[2]
                except OverflowError:
                    pass

        for tc in 'BHIL':
            a = array(tc)
            itembits = a.itemsize * 8
            vals = [0, 2 ** itembits - 1]
            a.fromlist(vals)
            assert a.tolist() == vals

            a = array(tc.lower())
            vals = [-1 * (2 ** itembits) // 2,  (2 ** itembits) // 2 - 1]
            a.fromlist(vals)
            assert a.tolist() == vals

    def test_float(self):
        values = [0, 1, 2.5, -4.25]
        for tc in 'fd':
            a = array(tc, values)
            assert len(a) == len(values)
            for i, v in enumerate(values):
                assert a[i] == v
                assert type(a[i]) is float
            a[1] = 10.125
            assert a[0] == 0
            assert a[1] == 10.125
            assert a[2] == 2.5
            assert len(a) == len(values)

    def test_itemsize(self):
        for t in 'cbB':
            assert(array(t).itemsize >= 1)
        for t in 'uhHiI':
            assert(array(t).itemsize >= 2)
        for t in 'lLf':
            assert(array(t).itemsize >= 4)
        for t in 'd':
            assert(array(t).itemsize >= 8)

        inttypes = 'bhil'
        for t in inttypes:
            a = array(t, [1, 2, 3])
            b = a.itemsize
            for v in (-2 ** (8 * b) // 2, 2 ** (8 * b) // 2 - 1):
                a[1] = v
                assert a[0] == 1 and a[1] == v and a[2] == 3
            raises(OverflowError, a.append, -2 ** (8 * b) // 2 - 1)
            raises(OverflowError, a.append, 2 ** (8 * b) // 2)

            a = array(t.upper(), [1, 2, 3])
            b = a.itemsize
            for v in (0, 2 ** (8 * b) - 1):
                a[1] = v
                assert a[0] == 1 and a[1] == v and a[2] == 3
            raises(OverflowError, a.append, -1)
            raises(OverflowError, a.append, 2 ** (8 * b))

    def test_errormessage(self):
        excinfo = raises(TypeError, "a = array(\"L\", [1, 2, 3])\na[0] = 'abc'")

    def test_fromstring(self):
        import sys

        a = array('c')
        a.fromstring('Hi!')
        assert a[0] == 'H' and a[1] == 'i' and a[2] == '!' and len(a) == 3
        a = array('c')
        a.fromstring(buffer('xyz'))
        exc = raises(TypeError, a.fromstring, memoryview('xyz'))
        assert a[0] == 'x' and a[1] == 'y' and a[2] == 'z' and len(a) == 3
        a = array('c')
        a.fromstring('')
        assert not len(a)

        for t in 'bBhHiIlLfd':
            a = array(t)
            a.fromstring('\x00' * a.itemsize * 2)
            assert len(a) == 2 and a[0] == 0 and a[1] == 0
            if a.itemsize > 1:
                raises(ValueError, a.fromstring, '\x00' * (a.itemsize - 1))
                raises(ValueError, a.fromstring, '\x00' * (a.itemsize + 1))
                raises(ValueError, a.fromstring, '\x00' * (2 * a.itemsize - 1))
                raises(ValueError, a.fromstring, '\x00' * (2 * a.itemsize + 1))
            b = array(t, b'\x00' * a.itemsize * 2)
            assert len(b) == 2 and b[0] == 0 and b[1] == 0
            if sys.version_info >= (2, 7, 11):
                raises(ValueError, a.fromstring, a)

    def test_fromlist(self):
        a = array('b')
        raises(OverflowError, a.fromlist, [1, 2, 400])
        assert len(a) == 0

        raises(OverflowError, a.extend, [1, 2, 400])
        assert len(a) == 2 and a[0] == 1 and a[1] == 2

        raises(OverflowError, array, 'b', [1, 2, 400])

        a = array('b', [1, 2])
        assert len(a) == 2 and a[0] == 1 and a[1] == 2

        a = array('b')
        raises(TypeError, a.fromlist, (1, 2, 400))

        raises(OverflowError, a.extend, (1, 2, 400))
        assert len(a) == 2 and a[0] == 1 and a[1] == 2

        raises(TypeError, a.extend, array('i', (7, 8)))
        assert len(a) == 2 and a[0] == 1 and a[1] == 2

        def gen():
            for i in range(4):
                yield i + 10
        a = array('i', gen())
        assert len(a) == 4 and a[2] == 12

        raises(OverflowError, array, 'b', (1, 2, 400))

        a = array('b', (1, 2))
        assert len(a) == 2 and a[0] == 1 and a[1] == 2

        a.extend(a)
        assert repr(a) == "array('b', [1, 2, 1, 2])"

    def test_fromunicode(self):
        raises(ValueError, array('i').fromunicode, u'hi')
        a = array('u')
        a.fromunicode(u'hi')
        assert len(a) == 2 and a[0] == 'h' and a[1] == 'i'

        b = array('u', u'hi')
        assert len(b) == 2 and b[0] == 'h' and b[1] == 'i'

    def test_setslice_to_extend(self):
        a = array('i')
        a[0:1] = array('i', [9])
        a[1:5] = array('i', [99])
        assert list(a) == [9, 99]

    def test_sequence(self):
        a = array('i', [1, 2, 3, 4])
        assert len(a) == 4
        assert a[0] == 1 and a[1] == 2 and a[2] == 3 and a[3] == 4
        assert a[-4] == 1 and a[-3] == 2 and a[-2] == 3 and a[-1] == 4
        a[-2] = 5
        assert a[0] == 1 and a[1] == 2 and a[2] == 5 and a[3] == 4

        for i in (4, -5):
            raises(IndexError, a.__getitem__, i)

        b = a[0:2]
        assert len(b) == 2 and b[0] == 1 and b[1] == 2
        b[0] = 6
        assert len(b) == 2 and b[0] == 6 and b[1] == 2
        assert a[0] == 1 and a[1] == 2 and a[2] == 5 and a[3] == 4
        assert a.itemsize == b.itemsize

        b = a[0:100]
        assert len(b) == 4
        assert b[0] == 1 and b[1] == 2 and b[2] == 5 and b[3] == 4

        l1 = [2 * i + 1 for i in range(10)]
        a1 = array('i', l1)
        for start in range(10):
            for stop in range(start, 10):
                for step in range(1, 10):
                    l2 = l1[start:stop:step]
                    a2 = a1[start:stop:step]
                    assert len(l2) == len(a2)
                    for i in range(len(l2)):
                        assert l2[i] == a2[i]

        a = array('i', [1, 2, 3, 4])
        a[1:3] = array('i', [5, 6])
        assert len(a) == 4
        assert a[0] == 1 and a[1] == 5 and a[2] == 6 and a[3] == 4
        a[0:-1:2] = array('i', [7, 8])
        assert a[0] == 7 and a[1] == 5 and a[2] == 8 and a[3] == 4

        raises(ValueError, "a = array('i', [1, 2, 3, 4])\na[1:2:4] = array('i', [5, 6, 7])")
        raises(TypeError, "a = array('i', [1, 2, 3, 4])\na[1:3] = array('I', [5, 6])")
        raises(TypeError, "a = array('i', [1, 2, 3, 4])\na[1:3] = [5, 6]")

        a = array('i', [1, 2, 3])
        assert a.__getslice__(1, 2) == a[1:2]
        a.__setslice__(1, 2, array('i', (7,)))
        assert a[0] == 1 and a[1] == 7 and a[2] == 3

    def test_resizingslice(self):
        a = array('i', [1, 2, 3])
        a[1:2] = array('i', [7, 8, 9])
        assert repr(a) == "array('i', [1, 7, 8, 9, 3])"
        a[1:2] = array('i', [10])
        assert repr(a) == "array('i', [1, 10, 8, 9, 3])"
        a[1:2] = array('i')
        assert repr(a) == "array('i', [1, 8, 9, 3])"

        a[1:3] = array('i', [11, 12, 13])
        assert repr(a) == "array('i', [1, 11, 12, 13, 3])"
        a[1:3] = array('i', [14])
        assert repr(a) == "array('i', [1, 14, 13, 3])"
        a[1:3] = array('i')
        assert repr(a) == "array('i', [1, 3])"

        a[1:1] = array('i', [15, 16, 17])
        assert repr(a) == "array('i', [1, 15, 16, 17, 3])"
        a[1:1] = array('i', [18])
        assert repr(a) == "array('i', [1, 18, 15, 16, 17, 3])"
        a[1:1] = array('i')
        assert repr(a) == "array('i', [1, 18, 15, 16, 17, 3])"

        a[:] = array('i', [20, 21, 22])
        assert repr(a) == "array('i', [20, 21, 22])"

    def test_reversingslice(self):
        a = array('i', [22, 21, 20])
        assert repr(a[::-1]) == "array('i', [20, 21, 22])"
        assert repr(a[2:1:-1]) == "array('i', [20])"
        assert repr(a[2:-1:-1]) == "array('i')"
        assert repr(a[-1:0:-1]) == "array('i', [20, 21])"

        for a in range(-4, 5):
            for b in range(-4, 5):
                for c in [-4, -3, -2, -1, 1, 2, 3, 4]:
                    lst = [1, 2, 3]
                    arr = array('i', lst)
                    assert repr(arr[a:b:c]) == repr(array('i', lst[a:b:c]))
                    for vals in ([4, 5], [6], []):
                        try:
                            ok = False
                            lst[a:b:c] = vals
                            ok = True
                            arr[a:b:c] = array('i', vals)
                            assert repr(arr) == repr(array('i', lst))
                        except ValueError:
                            assert not ok

    def test_toxxx(self):
        a = array('i', [1, 2, 3])
        l = a.tolist()
        assert type(l) is list and len(l) == 3
        assert a[0] == 1 and a[1] == 2 and a[2] == 3

        b = array('i', a.tostring())
        assert len(b) == 3 and b[0] == 1 and b[1] == 2 and b[2] == 3

        assert array('c', ('h', 'i')).tostring() == 'hi'
        a = array('i', [0, 0, 0])
        assert a.tostring() == '\x00' * 3 * a.itemsize
        s = array('i', [1, 2, 3]).tostring()
        assert '\x00' in s
        assert '\x01' in s
        assert '\x02' in s
        assert '\x03' in s
        a = array('i', s)
        assert a[0] == 1 and a[1] == 2 and a[2] == 3

    def test_empty_tostring(self):
        a = array('l')
        assert a.tostring() == b''

    def test_buffer(self):
        a = array('h', 'Hi')
        buf = buffer(a)
        assert buf[1] == 'i'

    def test_buffer_write(self):
        exc = raises(TypeError, """if 1:
        a = array('c', 'hello')
        buf = buffer(a)
        buf[3] = 'L'""")

    def test_buffer_keepalive(self):
        buf = buffer(array('c', 'text'))
        assert buf[2] == 'x'
        #
        a = array('c', 'foobarbaz')
        buf = buffer(a)
        a.fromstring('some extra text')
        assert buf[:] == 'foobarbazsome extra text'

    def test_list_methods(self):
        assert repr(array('i')) == "array('i')"
        assert repr(array('i', [1, 2, 3])) == "array('i', [1, 2, 3])"
        assert repr(array('h')) == "array('h')"

        a = array('i', [1, 2, 3, 1, 2, 1])
        assert a.count(1) == 3
        assert a.count(2) == 2
        assert a.index(3) == 2
        assert a.index(2) == 1
        raises(ValueError, a.index, 10)

        a.reverse()
        assert repr(a) == "array('i', [1, 2, 1, 3, 2, 1])"

        b = array('i', [1, 2, 3, 1, 2])
        b.reverse()
        assert repr(b) == "array('i', [2, 1, 3, 2, 1])"

        a.remove(3)
        assert repr(a) == "array('i', [1, 2, 1, 2, 1])"
        a.remove(1)
        assert repr(a) == "array('i', [2, 1, 2, 1])"

        a.pop()
        assert repr(a) == "array('i', [2, 1, 2])"

        a.pop(1)
        assert repr(a) == "array('i', [2, 2])"

        a.pop(-2)
        assert repr(a) == "array('i', [2])"

        a.insert(1, 7)
        assert repr(a) == "array('i', [2, 7])"
        a.insert(0, 8)
        a.insert(-1, 9)
        assert repr(a) == "array('i', [8, 2, 9, 7])"

        a.insert(100, 10)
        assert repr(a) == "array('i', [8, 2, 9, 7, 10])"
        a.insert(-100, 20)
        assert repr(a) == "array('i', [20, 8, 2, 9, 7, 10])"

    def test_compare(self):
        class comparable(object):
            def __eq__(self, other):
                return True
        class incomparable(object):
            pass

        for v1, v2, tt in (([1, 2, 3], [1, 3, 2], 'bhilBHIL'),
                         ('abc', 'acb', 'c'),
                         (u'abc', u'acb', 'u')):
            for t in tt:
                a = array(t, v1)
                b = array(t, v1)
                c = array(t, v2)

                assert (a == 7) is False
                assert (comparable() == a) is True
                assert (a == comparable()) is True
                assert (a == incomparable()) is False
                assert (incomparable() == a) is False

                assert (a == a) is True
                assert (a == b) is True
                assert (b == a) is True
                assert (a == c) is False
                assert (c == a) is False

                assert (a != a) is False
                assert (a != b) is False
                assert (b != a) is False
                assert (a != c) is True
                assert (c != a) is True

                assert (a < a) is False
                assert (a < b) is False
                assert (b < a) is False
                assert (a < c) is True
                assert (c < a) is False

                assert (a > a) is False
                assert (a > b) is False
                assert (b > a) is False
                assert (a > c) is False
                assert (c > a) is True

                assert (a <= a) is True
                assert (a <= b) is True
                assert (b <= a) is True
                assert (a <= c) is True
                assert (c <= a) is False

                assert (a >= a) is True
                assert (a >= b) is True
                assert (b >= a) is True
                assert (a >= c) is False
                assert (c >= a) is True

        a = array('i', [-1, 0, 1, 42, 0x7f])
        assert not a == 2*a
        assert a != 2*a
        assert a < 2*a
        assert a <= 2*a
        assert not a > 2*a
        assert not a >= 2*a

    def test_addmul(self):
        a = array('i', [1, 2, 3])
        assert repr(a + a) == "array('i', [1, 2, 3, 1, 2, 3])"
        assert 2 * a == a + a
        assert a * 2 == a + a
        b = array('i', [4, 5, 6, 7])
        assert repr(a + b) == "array('i', [1, 2, 3, 4, 5, 6, 7])"
        assert repr(2 * array('i')) == "array('i')"
        assert repr(array('i') + array('i')) == "array('i')"

        a = array('i', [1, 2])
        assert type(a + a) is array
        assert type(a * 2) is array
        assert type(2 * a) is array
        b = a
        a += a
        assert repr(b) == "array('i', [1, 2, 1, 2])"
        b *= 3
        assert repr(a) == "array('i', [1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2])"
        assert a == b
        a += array('i', (7,))
        assert repr(a) == "array('i', [1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 7])"

        class addable(object):
            def __add__(self, other):
                return "add"

            def __radd__(self, other):
                return "radd"

        assert addable() + array('i') == 'add'
        assert array('i') + addable() == 'radd'

        a = array('i')
        a += addable()
        assert a == 'radd'

        a = array('i', [1, 2])
        assert a * -1 == array('i')
        b = a
        a *= -1
        assert a == array('i')
        assert b == array('i')

        a = array('i')
        raises(TypeError, "a = array('i')\na * 'hi'")
        raises(TypeError, "a = array('i')\n'hi' * a")
        raises(TypeError, "a = array('i')\na *= 'hi'")

        class mulable(object):
            def __mul__(self, other):
                return "mul"

            def __rmul__(self, other):
                return "rmul"

        assert mulable() * array('i') == 'mul'
        assert array('i') * mulable() == 'rmul'

        a = array('i')
        a *= mulable()
        assert a == 'rmul'

    def test_delitem(self):
        a = array('i', [1, 2, 3])
        del a[1]
        assert repr(a) == "array('i', [1, 3])"

        a = array('i', [1, 2, 3, 4, 5])
        del a[1:3]
        assert repr(a) == "array('i', [1, 4, 5])"

        a.__delslice__(0, 2)
        assert repr(a) == "array('i', [5])"

        a = array('i', [1, 2, 3, 4, 5])
        del a[3:1]
        assert repr(a) == "array('i', [1, 2, 3, 4, 5])"

        del a[-100:1]
        assert repr(a) == "array('i', [2, 3, 4, 5])"

        del a[3:]
        assert repr(a) == "array('i', [2, 3, 4])"

        del a[-1:]
        assert repr(a) == "array('i', [2, 3])"

        del a[1:100]
        assert repr(a) == "array('i', [2])"

    def test_iter(self):
        a = array('i', [1, 2, 3])
        assert 1 in a
        b = array('i')
        for i in a:
            b.append(i)
        assert repr(b) == "array('i', [1, 2, 3])"
        assert hasattr(b, '__iter__')
        assert next(b.__iter__()) == 1

    def test_lying_iterable(self):
        class lier(object):
            def __init__(self, n):
                self.n = n

            def __len__(self):
                return 3

            def next(self):
                self.n -= 1
                if self.n < 0:
                    raise StopIteration
                return self.n

            def __iter__(self):
                return self

        assert len(lier(2)) == 3
        assert len(tuple(lier(2))) == 2
        a = array('i', lier(2))
        assert repr(a) == "array('i', [1, 0])"

        assert len(lier(5)) == 3
        assert len(tuple(lier(5))) == 5
        a = array('i', lier(5))
        assert repr(a) == "array('i', [4, 3, 2, 1, 0])"

    def test_type(self):
        for t in 'bBhHiIlLfdcu':
            assert type(array(t)) is array
            assert isinstance(array(t), array)

    def test_override_from(self):
        class mya(array):
            def fromlist(self, lst):
                self.append(7)

            def fromstring(self, lst):
                self.append('8')

            def fromunicode(self, lst):
                self.append(u'9')

            def extend(self, lst):
                self.append(10)

        assert repr(mya('c', 'hi')) == "array('c', 'hi')"
        assert repr(mya('u', u'hi')) == "array('u', u'hi')"
        assert repr(mya('i', [1, 2, 3])) == "array('i', [1, 2, 3])"
        assert repr(mya('i', (1, 2, 3))) == "array('i', [1, 2, 3])"

        a = mya('i')
        a.fromlist([1, 2, 3])
        assert repr(a) == "array('i', [7])"

        a = mya('c')
        a.fromstring('hi')
        assert repr(a) == "array('c', '8')"

        a = mya('u')
        a.fromunicode(u'hi')
        assert repr(a) == "array('u', u'9')"

        a = mya('i')
        a.extend([1, 2, 3])
        assert repr(a) == "array('i', [10])"

    def test_override_to(self):
        class mya(array):
            def tolist(self):
                return 'list'

            def tostring(self):
                return 'str'

            def tounicode(self):
                return 'unicode'

        assert mya('i', [1, 2, 3]).tolist() == 'list'
        assert mya('c', 'hi').tostring() == 'str'
        assert mya('u', u'hi').tounicode() == 'unicode'

        assert repr(mya('c', 'hi')) == "array('c', 'hi')"
        assert repr(mya('u', u'hi')) == "array('u', u'hi')"
        assert repr(mya('i', [1, 2, 3])) == "array('i', [1, 2, 3])"
        assert repr(mya('i', (1, 2, 3))) == "array('i', [1, 2, 3])"

    def test_unicode_outofrange(self):
        a = array('u', u'\x01\u263a\x00\ufeff')
        b = array('u', u'\x01\u263a\x00\ufeff')
        b.byteswap()
        assert a != b

    def test_unicode_ord_positive(self):
        import sys
        if sys.maxunicode == 0xffff:
            skip("test for 32-bit unicodes")
        a = array('u', b'\xff\xff\xff\xff')
        assert len(a) == 1
        assert repr(a[0]) == "u'\Uffffffff'"
        if sys.maxint == 2147483647:
            assert ord(a[0]) == -1
        else:
            assert ord(a[0]) == 4294967295

    def test_assign_object_with_special_methods(self):
        from array import array

        class Num(object):
            def __float__(self):
                return 5.25

            def __int__(self):
                return 7

        class NotNum(object):
            pass

        class Silly(object):
            def __float__(self):
                return None

            def __int__(self):
                return None

        class OldNum:
            def __float__(self):
                return 6.25

            def __int__(self):
                return 8

        class OldNotNum:
            pass

        class OldSilly:
            def __float__(self):
                return None

            def __int__(self):
                return None

        for tc in 'bBhHiIlL':
            a = array(tc, [0])
            raises(TypeError, a.__setitem__, 0, 1.0)
            a[0] = 1
            a[0] = Num()
            assert a[0] == 7
            raises(TypeError, a.__setitem__, NotNum())
            a[0] = OldNum()
            assert a[0] == 8
            raises(TypeError, a.__setitem__, OldNotNum())
            raises(TypeError, a.__setitem__, Silly())
            raises(TypeError, a.__setitem__, OldSilly())

        for tc in 'fd':
            a = array(tc, [0])
            a[0] = 1.0
            a[0] = 1
            a[0] = Num()
            assert a[0] == 5.25
            raises(TypeError, a.__setitem__, NotNum())
            a[0] = OldNum()
            assert a[0] == 6.25
            raises(TypeError, a.__setitem__, OldNotNum())
            raises(TypeError, a.__setitem__, Silly())
            raises(TypeError, a.__setitem__, OldSilly())

        a = array('c', 'hi')
        a[0] = 'b'
        assert a[0] == 'b'

        a = array('u', u'hi')
        a[0] = u'b'
        assert a[0] == u'b'

    def test_array_reverse_slice_assign_self(self):
        a = array('b', range(4))
        a[::-1] = a
        assert a == array('b', [3, 2, 1, 0])

    def test_array_multiply(self):
        a = array('b', [0])
        b = a * 13
        assert b[12] == 0
        b = 13 * a
        assert b[12] == 0
        a *= 13
        assert a[12] == 0
        a = array('b', [1])
        b = a * 13
        assert b[12] == 1
        b = 13 * a
        assert b[12] == 1
        a *= 13
        assert a[12] == 1
        a = array('i', [0])
        b = a * 13
        assert b[12] == 0
        b = 13 * a
        assert b[12] == 0
        a *= 13
        assert a[12] == 0
        a = array('i', [1])
        b = a * 13
        assert b[12] == 1
        b = 13 * a
        assert b[12] == 1
        a *= 13
        assert a[12] == 1
        a = array('i', [0, 0])
        b = a * 13
        assert len(b) == 26
        assert b[22] == 0
        b = 13 * a
        assert len(b) == 26
        assert b[22] == 0
        a *= 13
        assert a[22] == 0
        assert len(a) == 26
        a = array('f', [-0.0])
        b = a * 13
        assert len(b) == 13
        assert str(b[12]) == "-0.0"
        a = array('d', [-0.0])
        b = a * 13
        assert len(b) == 13
        assert str(b[12]) == "-0.0"

    def test_fresh_array_buffer_str(self):
        assert str(buffer(array('i'))) == ''

def raises(expected_exception, *args, **kwargs):
    try:
        if isinstance(args[0], str):
            exec(args[0])
        else:
            func = args[0]
            func(*args[1:], **kwargs)
    except expected_exception:
        return True
    message = "DID NOT RAISE {}".format(expected_exception)
    print message
    assert False, message
