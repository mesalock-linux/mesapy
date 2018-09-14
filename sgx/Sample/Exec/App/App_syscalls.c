#if defined(__cplusplus)
extern "C" {
#endif

#include <errno.h>
#include <stdio.h>
#include <unistd.h>

ssize_t ocall_write(int fd, const void *buf, size_t count){
    ssize_t ret = write(fd, buf, count);
    if (ret==-1)	{
     printf("ocall_write error is: %s \n", strerror(errno));
    }
    return ret;    
}

#if defined(__cplusplus)
}
#endif
