#if defined(__cplusplus)
extern "C" {
#endif
#include <string.h>
#include <time.h>
#include "Enclave_t.h"
#include "sys/types.h"
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


int sprintf(char *result, const char *format, ...){

	return 0;

}



void ocall_printf(const char *fmt, ...)
{
    char buf[BUFSIZ] = {'\0'};
    va_list ap;
    va_start(ap, fmt);
    vsnprintf(buf, BUFSIZ, fmt, ap);
    va_end(ap);
    ocall_print_string(buf);
}


#if defined(__cplusplus)
}
#endif
          
