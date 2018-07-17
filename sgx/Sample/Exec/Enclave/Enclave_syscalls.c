#if defined(__cplusplus)
extern "C" {
#endif
#include <string.h>
#include "Enclave_t.h"
#include <stdarg.h>
#include <stdio.h>      /* vsnprintf */
#include "extralib.h"
#include "Enclave.h"


extern void* sgx_ocalloc(unsigned long size);
extern void sgx_ocfree(void);

unsigned long write(long fd, long buf, long count){
        unsigned long ret = -1;
        unsigned char* buf1;
        buf1 = (unsigned char*)sgx_ocalloc(count);
        memcpy(buf1, (void*)buf, count);
        ocall_syscall3(&ret, WRITE, fd, (long)buf1, count);
        sgx_ocfree();
        return ret;
}

#if defined(__cplusplus)
}
#endif
          
