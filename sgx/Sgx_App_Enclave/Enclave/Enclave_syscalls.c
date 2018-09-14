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

ssize_t write(int fd, const void *buf, size_t count){
        ssize_t ret = -1;
        ocall_write(&ret, fd, buf, count);	
        return ret;
}

#if defined(__cplusplus)
}
#endif
          
