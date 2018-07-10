#define WRITE 1

unsigned long open(long pathname, long flags, long mode);
unsigned long close(long fd);
unsigned long unlink(long pathname);
unsigned long readlink(long path, long buf, long bufsiz);
unsigned long access(long pathname, long mode);
unsigned long clock_gettime(long clk_id, long tp);
unsigned long clock_getres(long clk_id, long res);
unsigned long getsid(long pid);
unsigned long read(long fd, long buf, long count);
unsigned long write(long fd, long buf, long count);
unsigned long fcntl(long int fd, int cmd, long arg);
unsigned long select(long nfds, long readfds, long writefds,
                  long exceptfds, long timeout);
unsigned long accept(long sockfd, long addr, long addrlen);
unsigned long lseek(long fd, long offset, long whence);
unsigned long lstat64(long pathname, long statbuf);
unsigned long stat64(long pathname, long statbuf);
unsigned long fstat64(long fd, long statbuf);
unsigned long exit_group(long status);
unsigned long execve(long filename, long argv, long envp);
unsigned long getcwd(long buf, long size);
unsigned long mmap(long addr, long length, long port, long flags, long fd, long offset);
int sprintf(char *result, const char *format, ...);
void ocall_printf(const char *fmt, ...);

#define fprintf()
