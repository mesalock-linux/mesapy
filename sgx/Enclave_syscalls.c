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


unsigned long open(long pathname, long flags, long mode){
        unsigned long ret = -1;
        unsigned long len = strnlen((const char*) pathname, PATH_MAX);
        void* buf = sgx_ocalloc(len+1);
        strncpy(buf, (const char*) pathname, len+1);
        ocall_syscall3(&ret, OPEN, (long)buf, flags, mode);
        sgx_ocfree();
        return ret;
}

unsigned long open2(long pathname, long flags){
        unsigned long ret = -1;
        unsigned long len = strnlen((const char*) pathname, PATH_MAX);
        void* buf = sgx_ocalloc(len+1);
        strncpy(buf, (const char*) pathname, len+1);
        ocall_syscall3(&ret, OPEN, (long)buf, flags, 0);
	sgx_ocfree();
        return ret;
}

unsigned long close(long fd){
        unsigned long ret = -1;
        ocall_syscall1(&ret, CLOSE, fd);
        return ret;
}

unsigned long unlink(long pathname){
        unsigned long ret = -1;
	unsigned long len = strnlen((const char*) pathname, PATH_MAX);
        void* buf = sgx_ocalloc(len+1);
        strncpy(buf, (const char*) pathname, len+1);
        ocall_syscall1(&ret, UNLINK, (long)(buf));
	sgx_ocfree();
        return ret;
}

unsigned long readlink(long path, long buf, long bufsiz){
        unsigned long ret = -1;
	unsigned char* buf1;
        buf1 = (unsigned char*)sgx_ocalloc(bufsiz);
	unsigned long len = strnlen((const char*) path, PATH_MAX);
        void* bufpath = sgx_ocalloc(len+1);
        strncpy(bufpath, (const char*) path, len+1);
        ocall_syscall3(&ret, READLINK, (long)bufpath, (long)buf1, bufsiz);
        memcpy((void*)buf, buf1, bufsiz);
        sgx_ocfree();
        return ret;
}

unsigned long access(long pathname, long mode){
        unsigned long ret = -1;
        unsigned long len = strnlen((const char*) pathname, PATH_MAX);
        void* buf = sgx_ocalloc(len+1);
        strncpy(buf, (const char*) pathname, len+1);
	ocall_syscall2(&ret, ACCESS, (long)(buf), mode);
        sgx_ocfree();
        return ret;

}

unsigned long readv(long fd, long iov, long iovcnt){
        unsigned long total = 0;
        long i,j = 0;
        unsigned char* buf;
        unsigned long* sbuf;
        unsigned long iovec_offs = 0;
        unsigned long offset = 0;
        unsigned long ret = -1;
        struct iovec* iovs = (struct iovec*) iov;
        total = iovcnt*sizeof(struct iovec);//First, we copy all the strucs, then the arrays 
        offset = total;//Set the offset to reside after the structs so all strings are copied after the structs
        for( i = 0; i < iovcnt; i++ ){
                total += iovs[i].iov_len;
        }
        buf = (unsigned char*)sgx_ocalloc(total);
        for( i = 0; i < iovcnt; i++ ){
                memcpy(buf+iovec_offs, &iovs[i], sizeof(struct iovec));
                ((struct iovec*) (buf+iovec_offs))->iov_base = (buf + offset);//Set new iovec to point to address of new string buffer
                iovec_offs += sizeof(struct iovec);
                offset += iovs[i].iov_len;
        }
        ocall_syscall3(&ret, READV, fd, (long)buf, iovcnt);
        offset = iovcnt*sizeof(struct iovec);
        iovec_offs = 0;
        for( i = 0; i < iovcnt; i++ ){
                iovec_offs += sizeof(struct iovec);
                memcpy(iovs[i].iov_base, buf+offset, iovs[i].iov_len);//Copy back in to buffer
                offset += iovs[i].iov_len;
        }
        sgx_ocfree();
        if (ret > total){abort();}
        return ret;
}
unsigned long writev(long fd, long iov, long iovcnt){
        unsigned long total = 0;
        long i,j = 0;
        unsigned char* buf;
        unsigned long* sbuf;
        unsigned long iovec_offs = 0;
        unsigned long offset = 0;
        unsigned long ret = -1;
        struct iovec* iovs = (struct iovec*) iov;
        total = iovcnt*sizeof(struct iovec);//First, we copy all the strucs, then the arrays 
        offset = total;//Set the offset to reside after the structs so all strings are copied after the structs
        for( i = 0; i < iovcnt; i++ ){
                total += iovs[i].iov_len;
        }
        buf = (unsigned char*)sgx_ocalloc(total);
        for( i = 0; i < iovcnt; i++ ){
                memcpy(buf+iovec_offs, &iovs[i], sizeof(struct iovec));
                ((struct iovec*) (buf+iovec_offs))->iov_base = (buf + offset);//Set new iovec to point to address of new string buffer
                iovec_offs += sizeof(struct iovec);
                memcpy(buf+offset, iovs[i].iov_base, iovs[i].iov_len);
                offset += iovs[i].iov_len;
        }
        ocall_syscall3(&ret, WRITEV, fd, (long)buf, iovcnt);
        sgx_ocfree();
        return ret;
}

unsigned long clock_gettime(long clk_id, long tp){
        unsigned char* buf;
        unsigned long ret = -1;
        buf = (unsigned char*)sgx_ocalloc(sizeof(struct timespec));
        ocall_syscall2(&ret, CLOCK_GETTIME, clk_id, (long)buf);
        memcpy((struct timespec *)tp, buf, sizeof(struct timespec));
        sgx_ocfree();
        return ret;
}

unsigned long clock_getres(long clk_id, long res){
        unsigned char* buf;
        unsigned long ret = -1;
        buf = (unsigned char*)sgx_ocalloc(sizeof(struct timespec));
        ocall_syscall2(&ret, CLOCK_GETRES, clk_id, (long)buf);
        memcpy((struct timespec *)res, buf, sizeof(struct timespec));
        sgx_ocfree();
        return ret;
}

unsigned long getsid(long pid){
        unsigned long ret = -1;
        ocall_syscall1(&ret, GETSID , pid);
        return ret;
}
unsigned long read(long fd, long buf, long count){
        unsigned long ret = -1;
        unsigned char* buf1;
        buf1 = (unsigned char*)sgx_ocalloc(count);
        ocall_syscall3(&ret, READ, fd, (long)buf1, count);
        memcpy((void*)buf, buf1, count);
        sgx_ocfree();
        return ret;
}

unsigned long write(long fd, long buf, long count){
        unsigned long ret = -1;
        unsigned char* buf1;
        buf1 = (unsigned char*)sgx_ocalloc(count);
        memcpy(buf1, (void*)buf, count);
        ocall_syscall3(&ret, WRITE, fd, (long)buf1, count);
        sgx_ocfree();
        return ret;
}

unsigned long fcntl(long int fd, int cmd, long arg){
        unsigned long ret = -1;
        ocall_syscall3(&ret, FCNTL, fd, cmd, arg);
        return ret;
}

unsigned long select(long nfds, long readfds, long writefds,
                  long exceptfds, long timeout){
        unsigned long ret = -1;
        unsigned char *read;
        unsigned char *write;
        unsigned char *except;
        unsigned char *time;

        ocall_malloc(&read, sizeof(struct enclave_fd_set));
        ocall_malloc(&write, sizeof(struct enclave_fd_set));
        ocall_malloc(&except, sizeof(struct enclave_fd_set));
        ocall_malloc(&time, sizeof(struct timeval));

        if((struct enclave_fd_set*)readfds != NULL)
        {
		memcpy(read, (struct enclave_fd_set*)readfds, sizeof(struct enclave_fd_set));
	}
        else
        {
                read = NULL;
        }
        if((struct enclave_fd_set*)writefds != NULL)
	{
		memcpy(write, (struct enclave_fd_set*)writefds, sizeof(struct enclave_fd_set));}
        else
        {
                write = NULL;
        }
        if((struct enclave_fd_set*)exceptfds != NULL)
        {
                memcpy(except, (struct enclave_fd_set*)exceptfds, sizeof(struct enclave_fd_set));
        }
        else
        {
                except = NULL;
        }

        if((struct timeval*)timeout != NULL)
        {
       	        memcpy(time, (struct timeval*)timeout, sizeof(struct timeval));
        }
        else
        {
                time = NULL;
        }
	ocall_syscall5(&ret, SELECT, nfds, (long)read, (long)write, (long)except, (long)time );

        if(time != NULL)
	{
        	memcpy(timeout, time, sizeof(struct timeval));
        }

        if(read != NULL)
	{
        	memcpy(readfds, read, sizeof(struct enclave_fd_set));
        }

        if(write != NULL)
	{
        	memcpy(writefds, write, sizeof(struct enclave_fd_set));
        }

        if(except != NULL)
	{
        	memcpy(exceptfds, except, sizeof(struct enclave_fd_set));
        }

        ocall_free(read);
        ocall_free(write);
        ocall_free(except);
        ocall_free(time);
        return ret;
}

unsigned long accept(long sockfd, long addr, long addrlen){
        unsigned long ret = -1;
        unsigned char* buffer;
        int len;
        if((int*) addrlen != NULL)
	{
                len = *((int*)addrlen);
        }
        else
        {
                len = 0;
        }
        buffer = (unsigned char*)sgx_ocalloc(sizeof(struct enclave_sockaddr) + sizeof(int));
        memset(buffer, 0, sizeof(struct enclave_sockaddr));
        *(buffer+len) = len;
        ocall_syscall3(&ret, ACCEPT, sockfd, (long)buffer, (long)(buffer+len) );
        memcpy(addr, buffer, len);
        *((int*)addrlen) = *(int*)(buffer+len);
        sgx_ocfree();
        return ret;
}

unsigned long lseek(long fd, long offset, long whence){
        unsigned long ret = -1;
        ocall_syscall3(&ret, LSEEK, fd, offset, whence);
        return ret;
}

unsigned long lstat64(long pathname, long statbuf){
        int c =1;
        char* p = (char*)pathname;
        while(*p != '\0')
	{
                c++;
                (char*)p++;
        }
        unsigned long ret = -1;
        unsigned char* buffer;
        buffer = (unsigned char *)sgx_ocalloc(c+sizeof(struct stat64));
        memcpy(buffer, pathname, c);
        ocall_syscall2(&ret, LSTAT, (long)buffer, (long)(buffer+c));
        memcpy((struct stat64 *)statbuf, (buffer+c), sizeof(struct stat64));
        sgx_ocfree();
        return ret;
}

unsigned long stat64(long pathname, long statbuf){
        int c =1;
        char* p = (char*)pathname;
        while(*p != '\0')
	{
                c++;
                (char*)p++;
        }
        unsigned long ret = -1;
        unsigned char* buffer;
        buffer = (unsigned char *)sgx_ocalloc(c+sizeof(struct stat64));
        memcpy(buffer, pathname, c);
        ocall_syscall2(&ret, STAT, (long)buffer, (long)(buffer+c));
        memcpy((struct stat64 *)statbuf, (buffer+c), sizeof(struct stat64));
        sgx_ocfree();
        return ret;
}

unsigned long fstat64(long fd, long statbuf){
        unsigned long ret = -1;
        unsigned char* buffer;
        buffer = (unsigned char *)sgx_ocalloc(sizeof(struct stat64));
        ocall_syscall2(&ret, FSTAT, fd, (long)(buffer));
        memcpy((struct stat64 *)statbuf, (buffer), sizeof(struct stat64));
        sgx_ocfree();
        return ret;

}

unsigned long exit_group(long status){
        unsigned long ret;
        ocall_syscall1(&ret, EXIT_GROUP, status);
        return ret;

}

unsigned long execve(long filename, long argv, long envp){
        unsigned long ret = -1;
        unsigned char* buffer;
        int c =1;
        char* p = (char*)filename;
        while(*p != '\0')
	{
                c++;
                (char*)p++;
        }
        buffer = (unsigned char *)sgx_ocalloc(c+128);
        ocall_syscall3(&ret, EXECVE, (long) buffer, (long)(buffer+c), NULL);
	sgx_ocfree();
        return ret;
}

char* getcwd(char* buf, long size){
        char* ret = NULL;
        char* buffer;
        buffer = (char *)sgx_ocalloc(size);
        ocall_syscall2(&ret, GETCWD, (long)buffer, (long)size);
        memcpy(buf, buffer, size);
	sgx_ocfree();
        return buf;
}

unsigned long mmap(long addr, long length, long port, long flags, long fd, long offset ){
        unsigned long ret = -1;
        unsigned char * buffer;
        ocall_printf("in mmap bridge function");
        buffer = (unsigned char *)sgx_ocalloc(8*sizeof(long));
        if(addr != NULL)
	{
        	memcpy(buffer, addr, 8*sizeof(long));}
        else
	{
                buffer = NULL;
        }
        ocall_syscall6(&ret, MMAP, (long)buffer, length, port, flags, fd, offset );
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

char ** environ =NULL;


void run_pypy(int argc, char *argv[]){
	ocall_environ(&environ);
        int result = compute_num(12, 10);
	ocall_printf("The result: %d\n", result);
        my_helloworld();
	char a[20] = "print \"hello world\"";
	ocall_printf("string in a is %s", a);
	testexec(a);
}


#if defined(__cplusplus)
}
#endif
          
