from ffi import ffi
import _numpypy as np

@ffi.def_extern()
def micronumpy():
    multiarray_example(10)

def multiarray_example(n):
    x = get_matrix(n)
    print "x: ", x
    y = get_matrix(n)
    print "y: ", y
    z = x.dot(y)
    print "x dot y: ", z
    print "transpose z: ", z.transpose()
    print "get diagonal of z: ", z.diagonal()

def get_matrix(n):
    x = np.multiarray.zeros((n, n))
    for i in range(n):
        for j in range(n):
            x[i][j] = i * j
    return x
