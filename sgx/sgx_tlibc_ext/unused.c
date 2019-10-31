/*
 * This file contains symbols which are not supported for now. This is just a
 * temporary workaround. The enclave will abort if MesaPy for SGX calls these
 * functions for some reasons. We will gradually move useful functions into the
 * untrusted libc and remove unused or unsafe functions from MesaPy for SGX.
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>

__attribute__((weak)) int stderr = 3;

#define FILE void
#define pid_t int
#define mode_t int
#define clockid_t int
#define fd_set int
#define socklen_t int
#define off_t int
#define off64_t int
#define time_t long

__attribute__((weak)) struct sockaddr {
};

__attribute__((weak)) struct stat {
};

__attribute__((weak)) struct stat64 {
};

__attribute__((weak)) struct timespec {
};

__attribute__((weak)) struct timeval {
};

__attribute__((weak)) struct timezone {
    int tz_minuteswest;
    int tz_dsttime;
};

__attribute__((weak)) void *dlopen(const char *filename, int flag) { abort(); }

__attribute__((weak)) int dlclose(void *handle) { abort(); }

__attribute__((weak)) char *dlerror(void) { abort(); }

__attribute__((weak)) void *dlsym(void *handle, const char *symbol) { abort(); }

__attribute__((weak)) int isatty(int fd) { abort(); }

__attribute__((weak)) int ftruncate(int fd, off_t length) { abort(); }

__attribute__((weak)) int ftruncate64(int fd, off64_t length) { abort(); }

__attribute__((weak)) int madvise(void *addr, size_t length, int advice) { abort(); }

__attribute__((weak)) char *setlocale(int category, const char *locale) { abort(); }

__attribute__((weak)) char *nl_langinfo(int item) { abort(); }

__attribute__((weak)) struct lconv *localeconv(void) { abort(); }

__attribute__((weak)) int execv(const char *path, char *const argv[]) { abort(); }

__attribute__((weak)) char *getenv(const char *name) { abort(); }

__attribute__((weak)) int fork(void) { abort(); }

__attribute__((weak)) pid_t getpid(void) { abort(); }

__attribute__((weak)) int mprotect(void *addr, size_t len, int prot) { abort(); }

__attribute__((weak)) int prctl(int option, unsigned long arg2, unsigned long arg3,
          unsigned long arg4, unsigned long arg5)
{
    abort();
}

__attribute__((weak)) void _exit(int status) { abort(); }

__attribute__((weak)) void setbuf(void *stream, char *buf) { abort(); }

__attribute__((weak)) int fclose(void *stream) { abort(); }

__attribute__((weak)) void *fdopen(int fd, const char *mode) { abort(); }

__attribute__((weak)) int open(const char *pathname, int flags, mode_t mode) { abort(); }

__attribute__((weak)) int open64(const char *pathname, int flags, mode_t mode) { abort(); }

__attribute__((weak)) int close(int fd) { abort(); }

__attribute__((weak)) int unlink(const char *pathname) { abort(); }

__attribute__((weak)) ssize_t readlink(const char *pathname, char *buf, size_t bufsiz) { abort(); }

__attribute__((weak)) int access(const char *pathname, int mode) { abort(); }

__attribute__((weak)) int clock_gettime(clockid_t clk_id, struct timespec *tp) { abort(); }

__attribute__((weak)) int clock_getres(clockid_t clk_id, struct timespec *res) { abort(); }

__attribute__((weak)) ssize_t read(int fd, void *buf, size_t count) { abort(); }

__attribute__((weak)) int fcntl(int fd, int cmd, ... /* arg */) { abort(); }

__attribute__((weak)) int select(int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds,
           struct timeval *timeout)
{
    abort();
}

__attribute__((weak)) int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen) { abort(); }

__attribute__((weak)) off_t lseek(int fd, off_t offset, int whence) { abort(); }

__attribute__((weak)) off64_t lseek64(int fd, off64_t offset, int whence) { abort(); }

__attribute__((weak)) int lstat64(const char *pathname, struct stat *buf) { abort(); }

__attribute__((weak)) int stat(const char *pathname, struct stat *buf) { abort(); }

__attribute__((weak)) int fstat(int fd, struct stat *buf) { abort(); }

__attribute__((weak)) char *getcwd(char *buf, size_t size) { abort(); }

__attribute__((weak)) void *mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset)
{
    abort();
}

__attribute__((weak)) void *mmap64(void *addr, size_t length, int prot, int flags, int fd,
             off_t offset)
{
    abort();
}

__attribute__((weak)) void __assert_fail(const char *assertion, const char *file, unsigned int line,
                   const char *function)
{
    abort();
}

__attribute__((weak)) int __fprintf_chk(FILE *stream, int flag, const char *fmt, ...) { abort(); }

__attribute__((weak)) int __lxstat64(int vers, const char *name, struct stat64 *buf) { abort(); }

__attribute__((weak)) int __xstat64(int vers, const char *name, struct stat64 *buf) { abort(); }

__attribute__((weak)) int __fxstat64(int vers, int fd, struct stat64 *buf) { abort(); }

__attribute__((weak)) int gettimeofday(struct timeval *tv, struct timezone *tz) { abort(); };

__attribute__((weak)) time_t time(time_t *tloc) { abort(); };

#ifdef TEST_MESATEE_ABI
int c_read_file(char* context_id,
    char* context_token,
    char* file_id,
    char* out_buf,
    size_t out_buf_size) {
    char *content = "1234567890123456\0";
    int content_len = strlen(content);
    if (out_buf_size < content_len) return out_buf_size - content_len;

    strcpy(out_buf, content);
    return strlen(content);
}

int c_save_file_for_task_creator(char* context_id,
                                 char* context_token,
                                 char* in_buf,
                                 size_t in_buf_size,
                                 char* out_file_id_buf,
                                 size_t out_file_id_buf_size) {
    char *content = "1234567890123456\0";
    int content_len = strlen(content);
    if (out_file_id_buf_size < content_len) return out_file_id_buf_size - content_len;

    strcpy(out_file_id_buf, content);
    return strlen(content);
}

int c_save_file_for_all_participants(char* context_id,
                                     char* context_token,
                                     char* in_buf,
                                     size_t in_buf_size,
                                     char* out_file_id_buf,
                                     size_t out_file_id_buf_size) {
    char *content = "1234567890123456\0";
    int content_len = strlen(content);
    if (out_file_id_buf_size < content_len) return out_file_id_buf_size - content_len;

    strcpy(out_file_id_buf, content);
    return strlen(content);
}

int c_save_file_for_file_owner(char* context_id,
                               char* context_token,
                               char* in_buf,
                               size_t in_buf_size,
                               char* file_id,
                               char* out_file_id_buf,
                               size_t out_file_id_buf_size) {
    char *content = "1234567890123456\0";
    int content_len = strlen(content);
    if (out_file_id_buf_size < content_len) return out_file_id_buf_size - content_len;

    strcpy(out_file_id_buf, content);
    return strlen(content);
}
#endif
