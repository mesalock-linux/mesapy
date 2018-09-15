#include <stdio.h>
#include <unistd.h>

ssize_t u_write_ocall(int fd, const void *buf, size_t count)
{
    ssize_t ret = write(fd, buf, count);
    return ret;
}
