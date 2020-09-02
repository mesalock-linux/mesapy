from ffi import ffi
import marshal
import gc

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
        gc.collect()

        ret_bytes = []
        # Assert ret value is utf-8 encoded
        if ret is not None:
            ret_bytes = ret.encode("utf-8")

    except:
        return MESAPY_EXEC_ERROR

    if len(ret_bytes) > py_ret_max_len:
        return MESAPY_ERROR_BUFFER_TOO_SHORT

    for i in range(len(ret_bytes)):
        py_ret[i] = ret_bytes[i]

    return len(ret_bytes)
