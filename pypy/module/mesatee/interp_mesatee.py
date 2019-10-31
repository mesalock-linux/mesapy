from rpython.translator.tool.cbuild import ExternalCompilationInfo
from rpython.rlib.rstring import StringBuilder
from rpython.rtyper.lltypesystem import rffi, lltype
from pypy.interpreter.gateway import unwrap_spec

eci = ExternalCompilationInfo()

# int c_read_file(char* context_id,
#                 char* context_token,
#                 char* file_id,
#                 char* out_buf,
#                 size_t out_buf_size);
c_mesatee_read_file = rffi.llexternal('c_read_file',
                                      [
                                          rffi.CCHARP,    # context_id
                                          rffi.CCHARP,    # context_token
                                          rffi.CCHARP,    # file_id
                                          rffi.CCHARP,    # out_buf
                                          rffi.SIZE_T,    # out_buf_size
                                      ],
                                      rffi.INT,           # return type
                                      compilation_info=eci)

@unwrap_spec(context_id='text', context_token='text', file_id='text')
def mesatee_read_file(space, context_id, context_token, file_id):
    BASE_BUF_SIZE = 8
    buf = lltype.malloc(rffi.CCHARP.TO, BASE_BUF_SIZE, flavor='raw')
    ret = c_mesatee_read_file(context_id, context_token, file_id, buf, BASE_BUF_SIZE)
    if ret > 0:
        s = StringBuilder()
        s.append_charpsize(buf, ret)
        lltype.free(buf, flavor='raw')
        return space.newbytes(s.build())
    else:
        s = StringBuilder()
        lltype.free(buf, flavor='raw')
        buf = lltype.malloc(rffi.CCHARP.TO, BASE_BUF_SIZE - ret + 1, flavor='raw')
        ret = c_mesatee_read_file(context_id, context_token, file_id, buf, BASE_BUF_SIZE - ret + 1)
        s.append_charpsize(buf, ret)
        lltype.free(buf, flavor='raw')
        return space.newbytes(s.build())

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
    BASE_BUF_SIZE = 8
    buf = lltype.malloc(rffi.CCHARP.TO, BASE_BUF_SIZE, flavor='raw')
    ret = c_mesatee_save_file_for_task_creator(context_id, context_token, file_content, len(file_content), buf, BASE_BUF_SIZE)
    if ret > 0:
        s = StringBuilder()
        s.append_charpsize(buf, ret)
        lltype.free(buf, flavor='raw')
        return space.newbytes(s.build())
    else:
        s = StringBuilder()
        lltype.free(buf, flavor='raw')
        buf = lltype.malloc(rffi.CCHARP.TO, BASE_BUF_SIZE - ret + 1, flavor='raw')
        ret = c_mesatee_save_file_for_task_creator(context_id, context_token, file_content, len(file_content), buf, BASE_BUF_SIZE - ret + 1)
        s.append_charpsize(buf, ret)
        lltype.free(buf, flavor='raw')
        return space.newbytes(s.build())

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
    BASE_BUF_SIZE = 8
    buf = lltype.malloc(rffi.CCHARP.TO, BASE_BUF_SIZE, flavor='raw')
    ret = c_mesatee_save_file_for_all_participants(context_id, context_token, file_content, len(file_content), buf, BASE_BUF_SIZE)
    if ret > 0:
        s = StringBuilder()
        s.append_charpsize(buf, ret)
        lltype.free(buf, flavor='raw')
        return space.newbytes(s.build())
    else:
        s = StringBuilder()
        lltype.free(buf, flavor='raw')
        buf = lltype.malloc(rffi.CCHARP.TO, BASE_BUF_SIZE - ret + 1, flavor='raw')
        ret = c_mesatee_save_file_for_task_creator(context_id, context_token, file_content, len(file_content), buf, BASE_BUF_SIZE - ret + 1)
        s.append_charpsize(buf, ret)
        lltype.free(buf, flavor='raw')
        return space.newbytes(s.build())

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
    BASE_BUF_SIZE = 8
    buf = lltype.malloc(rffi.CCHARP.TO, BASE_BUF_SIZE, flavor='raw')
    ret = c_mesatee_save_file_for_file_owner(context_id, context_token, file_content, len(file_content), file_id, buf, BASE_BUF_SIZE)
    if ret > 0:
        s = StringBuilder()
        s.append_charpsize(buf, ret)
        lltype.free(buf, flavor='raw')
        return space.newbytes(s.build())
    else:
        s = StringBuilder()
        lltype.free(buf, flavor='raw')
        buf = lltype.malloc(rffi.CCHARP.TO, BASE_BUF_SIZE - ret + 1, flavor='raw')
        ret = c_mesatee_save_file_for_file_owner(context_id, context_token, file_content, len(file_content), file_id, buf, BASE_BUF_SIZE - ret + 1)
        s.append_charpsize(buf, ret)
        lltype.free(buf, flavor='raw')
        return space.newbytes(s.build())
