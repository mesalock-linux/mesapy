/*
 * This file contains symbols which are not supported for now. This is just a
 * temporary workaround. The enclave will abort if MesaPy for SGX calls these
 * functions for some reasons. We will gradually move useful functions into the
 * untrusted libc and remove unused or unsafe functions from MesaPy for SGX.
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

int stderr = 3;

#define FILE void
#define pid_t int
#define mode_t int
#define clockid_t int
#define fd_set int
#define socklen_t int
#define off_t int
#define off64_t int
#define time_t long

struct sockaddr {
};

struct stat {
};

struct stat64 {
};

struct timespec {
};

struct timeval {
};

struct timezone {
    int tz_minuteswest;
    int tz_dsttime;
};

void *dlopen(const char *filename, int flag) { abort(); }

int dlclose(void *handle) { abort(); }

char *dlerror(void) { abort(); }

void *dlsym(void *handle, const char *symbol) { abort(); }

int isatty(int fd) { abort(); }

int ftruncate(int fd, off_t length) { abort(); }

int ftruncate64(int fd, off64_t length) { abort(); }

int madvise(void *addr, size_t length, int advice) { abort(); }

char *setlocale(int category, const char *locale) { abort(); }

char *nl_langinfo(int item) { abort(); }

struct lconv *localeconv(void) { abort(); }

int execv(const char *path, char *const argv[]) { abort(); }

char *getenv(const char *name) { abort(); }

int fork(void) { abort(); }

pid_t getpid(void) { abort(); }

int mprotect(void *addr, size_t len, int prot) { abort(); }

int prctl(int option, unsigned long arg2, unsigned long arg3,
          unsigned long arg4, unsigned long arg5)
{
    abort();
}

void _exit(int status) { abort(); }

void setbuf(void *stream, char *buf) { abort(); }

int fclose(void *stream) { abort(); }

void *fdopen(int fd, const char *mode) { abort(); }

int open(const char *pathname, int flags, mode_t mode) { abort(); }

int open64(const char *pathname, int flags, mode_t mode) { abort(); }

int close(int fd) { abort(); }

int unlink(const char *pathname) { abort(); }

ssize_t readlink(const char *pathname, char *buf, size_t bufsiz) { abort(); }

int access(const char *pathname, int mode) { abort(); }

int clock_gettime(clockid_t clk_id, struct timespec *tp) { abort(); }

int clock_getres(clockid_t clk_id, struct timespec *res) { abort(); }

ssize_t read(int fd, void *buf, size_t count) { abort(); }

int fcntl(int fd, int cmd, ... /* arg */) { abort(); }

int select(int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds,
           struct timeval *timeout)
{
    abort();
}

int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen) { abort(); }

off_t lseek(int fd, off_t offset, int whence) { abort(); }

off64_t lseek64(int fd, off64_t offset, int whence) { abort(); }

int lstat64(const char *pathname, struct stat *buf) { abort(); }

int stat(const char *pathname, struct stat *buf) { abort(); }

int fstat(int fd, struct stat *buf) { abort(); }

char *getcwd(char *buf, size_t size) { abort(); }

void *mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset)
{
    abort();
}

void *mmap64(void *addr, size_t length, int prot, int flags, int fd,
             off_t offset)
{
    abort();
}

void __assert_fail(const char *assertion, const char *file, unsigned int line,
                   const char *function)
{
    abort();
}

int __fprintf_chk(FILE *stream, int flag, const char *fmt, ...) { abort(); }

int __lxstat64(int vers, const char *name, struct stat64 *buf) { abort(); }

int __xstat64(int vers, const char *name, struct stat64 *buf) { abort(); }

int __fxstat64(int vers, int fd, struct stat64 *buf) { abort(); }

int gettimeofday(struct timeval *tv, struct timezone *tz) { abort(); };

time_t time(time_t *tloc) { abort(); };
