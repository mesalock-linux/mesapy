#include <unistd.h>
#include <errno.h>

ssize_t u_write_ocall(int *p_errno, int fd, const void *buf, size_t count)
{
    int result = write(fd, buf, count);

    if (p_errno != NULL)
        *p_errno = errno;

    return result;
}
