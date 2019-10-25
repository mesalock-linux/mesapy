from ffi import ffi
import marshal

MESAPY_ERROR_BUFFER_TOO_SHORT = -1
MESAPY_EXEC_ERROR = -2

@ffi.def_extern()
def mesapy_exec(py_script, py_argc, py_argv, py_ret, py_ret_max_len):
    """
    execute python script (the `entrypoint` function), set the returned Python
    object to py_ret and return the length of it.
    """
    try:
        global_variables = {}
        exec(ffi.string(py_script)) in global_variables
        l = 0
        entrypoint_argv = []
        for i in range(py_argc):
            entrypoint_argv.append(ffi.string(py_argv[i]))
        global_variables["entrypoint_argv"] = entrypoint_argv
        ret = eval("entrypoint(entrypoint_argv)", global_variables)
    except:
        return MESAPY_EXEC_ERROR

    s = marshal.dumps(ret)

    if len(s) > py_ret_max_len:
        return MESAPY_ERROR_BUFFER_TOO_SHORT

    for i in range(len(s)):
        py_ret[i] = s[i]

    return len(s)
