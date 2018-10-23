#include <unistd.h>

ssize_t u_write_ocall(int fd, const void *buf, size_t count)
{
    return write(fd, buf, count);
}
