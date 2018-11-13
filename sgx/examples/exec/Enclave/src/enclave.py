from ffi import ffi
import marshal

MESAPY_ERROR_BUFFER_TOO_SHORT = -1
MESAPY_EXEC_ERROR = -2

@ffi.def_extern()
def mesapy_exec(py_script, py_ret, buflen):
    """
    execute python script (the `entrypoint` function), set the returned Python
    object to py_ret and return the length of it.
    """
    try:
        global_variables = {}
        exec(ffi.string(py_script)) in global_variables
        ret = eval("entrypoint()", global_variables)
    except:
        return MESAPY_EXEC_ERROR

    s = marshal.dumps(ret)

    if len(s) > buflen:
        return MESAPY_ERROR_BUFFER_TOO_SHORT

    for i in range(len(s)):
        py_ret[i] = s[i]

    return len(s)
