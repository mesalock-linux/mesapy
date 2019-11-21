from rpython.translator.tool.cbuild import ExternalCompilationInfo
from rpython.rlib.rstring import StringBuilder
from rpython.rtyper.lltypesystem import rffi, lltype
from pypy.interpreter.gateway import unwrap_spec
from pypy.interpreter.error import OperationError

class Cache:
    def __init__(self, space):
        self.w_error = space.new_exception_class("mesatee.error")

def mesatee_error(space, msg):
    w_error = space.fromcache(Cache).w_error
    return OperationError(w_error, space.newtext(msg))

eci = ExternalCompilationInfo()
BASE_BUF_SIZE = 64

# int c_read_file(char* context_id,
#                 char* context_token,
#                 char* file_id,
#                 char* out_buf,
#                 size_t* out_buf_size);
c_mesatee_read_file = rffi.llexternal('c_read_file',
                                      [
                                          rffi.CCHARP,    # context_id
                                          rffi.CCHARP,    # context_token
                                          rffi.CCHARP,    # file_id
                                          rffi.CCHARP,    # out_buf
                                          rffi.SIZE_TP,   # out_buf_size pointer
                                      ],
                                      rffi.INT,           # return type
                                      compilation_info=eci)

@unwrap_spec(context_id='text', context_token='text', file_id='text')
def mesatee_read_file(space, context_id, context_token, file_id):
    out_buf = lltype.malloc(rffi.CCHARP.TO, BASE_BUF_SIZE, flavor='raw')
    out_buf_size_p = lltype.malloc(rffi.SIZE_TP.TO, 1, flavor='raw')
    out_buf_size_p[0] = rffi.cast(rffi.SIZE_T, BASE_BUF_SIZE)

    ret = c_mesatee_read_file(context_id, context_token, file_id, out_buf, out_buf_size_p)
    if ret > 0:
        s = StringBuilder()
        s.append_charpsize(out_buf, ret)

        lltype.free(out_buf, flavor='raw')
        lltype.free(out_buf_size_p, flavor='raw')

        return space.newbytes(s.build())
    elif ret == -2:    # needs more spaces
        s = StringBuilder()
        lltype.free(out_buf, flavor='raw')

        out_buf = lltype.malloc(rffi.CCHARP.TO, out_buf_size_p[0], flavor='raw')
        ret = c_mesatee_read_file(context_id, context_token, file_id, out_buf, out_buf_size_p)
        s.append_charpsize(out_buf, ret)

        lltype.free(out_buf, flavor='raw')
        lltype.free(out_buf_size_p, flavor='raw')

        return space.newbytes(s.build())
    else:
        lltype.free(out_buf, flavor='raw')
        lltype.free(out_buf_size_p, flavor='raw')

        raise mesatee_error(space, "Cannot read file")

# int c_save_file_for_task_creator(char* context_id,
#                                  char* context_token,
#                                  char* in_buf,
#                                  size_t in_buf_size,
#                                  char* out_file_id_buf,
#                                  size_t out_file_id_buf_size);
c_mesatee_save_file_for_task_creator = \
    rffi.llexternal('c_save_file_for_task_creator',
                    [
                        rffi.CCHARP,    # context_id
                        rffi.CCHARP,    # context_token
                        rffi.CCHARP,    # in_buf
                        rffi.SIZE_T,    # in_buf_size
                        rffi.CCHARP,    # out_file_id_buf
                        rffi.SIZE_T,    # out_file_id_buf_size
                    ],
                    rffi.INT,
                    compilation_info=eci)

@unwrap_spec(context_id='text', context_token='text', file_content='text')
def mesatee_save_file_for_task_creator(space, context_id, context_token, file_content):
    out_file_id_buf = lltype.malloc(rffi.CCHARP.TO, BASE_BUF_SIZE, flavor='raw')
    ret = c_mesatee_save_file_for_task_creator(context_id, context_token, file_content, len(file_content), out_file_id_buf, BASE_BUF_SIZE)
    if ret > 0:
        s = StringBuilder()
        s.append_charpsize(out_file_id_buf, ret)
        lltype.free(out_file_id_buf, flavor='raw')
        return space.newbytes(s.build())
    else:
        lltype.free(out_file_id_buf, flavor='raw')
        raise mesatee_error(space, "Cannot save file")

# int c_save_file_for_all_participants(char* context_id,
#                                      char* context_token,
#                                      char* in_buf,
#                                      size_t in_buf_size,
#                                      char* out_file_id_buf,
#                                      size_t out_file_id_buf_size);

c_mesatee_save_file_for_all_participants = \
    rffi.llexternal('c_save_file_for_all_participants',
                    [
                        rffi.CCHARP,    # context_id
                        rffi.CCHARP,    # context_token
                        rffi.CCHARP,    # in_buf
                        rffi.SIZE_T,    # in_buf_size
                        rffi.CCHARP,    # out_file_id_buf
                        rffi.SIZE_T,    # out_file_id_buf_size
                    ],
                    rffi.INT,
                    compilation_info=eci)

@unwrap_spec(context_id='text', context_token='text', file_content='text')
def mesatee_save_file_for_all_participants(space, context_id, context_token, file_content):
    out_file_id_buf = lltype.malloc(rffi.CCHARP.TO, BASE_BUF_SIZE, flavor='raw')
    ret = c_mesatee_save_file_for_all_participants(context_id, context_token, file_content, len(file_content), out_file_id_buf, BASE_BUF_SIZE)
    if ret > 0:
        s = StringBuilder()
        s.append_charpsize(out_file_id_buf, ret)
        lltype.free(out_file_id_buf, flavor='raw')
        return space.newbytes(s.build())
    else:
        lltype.free(out_file_id_buf, flavor='raw')
        raise mesatee_error(space, "Cannot save file")

# int c_save_file_for_file_owner(char* context_id,
#                                char* context_token,
#                                char* in_buf,
#                                size_t in_buf_size,
#                                char* file_id,
#                                char* out_file_id_buf,
#                                size_t out_file_id_buf_size)

c_mesatee_save_file_for_file_owner = \
    rffi.llexternal('c_save_file_for_file_owner',
                    [
                        rffi.CCHARP,    # context_id
                        rffi.CCHARP,    # context_token
                        rffi.CCHARP,    # in_buf
                        rffi.SIZE_T,    # in_buf_size
                        rffi.CCHARP,    # file_id
                        rffi.CCHARP,    # out_file_id_buf
                        rffi.SIZE_T,    # out_file_id_buf_size
                    ],
                    rffi.INT,
                    compilation_info=eci)

@unwrap_spec(context_id='text', context_token='text', file_id='text', file_content='text')
def mesatee_save_file_for_file_owner(space, context_id, context_token, file_id, file_content):
    out_file_id_buf = lltype.malloc(rffi.CCHARP.TO, BASE_BUF_SIZE, flavor='raw')
    ret = c_mesatee_save_file_for_file_owner(context_id, context_token, file_content, len(file_content), file_id, out_file_id_buf, BASE_BUF_SIZE)
    if ret > 0:
        s = StringBuilder()
        s.append_charpsize(out_file_id_buf, ret)
        lltype.free(out_file_id_buf, flavor='raw')
        return space.newbytes(s.build())
    else:
        lltype.free(out_file_id_buf, flavor='raw')
        raise mesatee_error(space, "Cannot read file")
