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

char ** environ = "";

int dlclose(void * handle){

	return 0;
}

void *dlopen(const char* filename, int flag){

	return NULL;
}

char *dlerror(void){

	return NULL;
}

void *dlsym(void *handle, const char *symbol){

	return NULL;
}

int isatty(int fd){

	return 0;
}

int ftruncate(int fd, long length){

	return 0;
}

int uname(struct utsname *buf){

	return 0;
}

int madvise(void *addr, size_t length, int advice){

	return 0;
}

char *setlocale(int category, const char *locale){

	return NULL;
}

char *nl_langinfo(int item){

	return NULL;
}

struct lconv *localeconv(void){

	return NULL;
}

int execv(const char *path, char *const argv[]){

	return -1;
}

char *getenv(const char *name){

	return NULL;
}

long syscall(long number, ...){

	return -1;
}

int fork(void){

	return; 
}

int getpid(void){

	return;
}

int mprotect(void *addr, size_t len, int prot){

	return;
}

int prctl(int option, unsigned long arg2, unsigned long arg3,
                 unsigned long arg4, unsigned long arg5){

	return;
}

void _exit(int status){

	return;	
}

void setbuf(void *stream, char *buf){

	return;
}

int fclose(void* stream){

        return 0;
}

void *fdopen(int fd, const char *mode){

	return NULL;
}

int open(const char *pathname, int flags, mode_t mode){

	return;
}

int close(int fd){

	return;
}

int unlink(const char *pathname){

	return;
}

ssize_t readlink(const char *pathname, char *buf, size_t bufsiz){

	return;
}

int access(const char *pathname, int mode){

	return;
}

int clock_gettime(clockid_t clk_id, struct timespec *tp){

	return;
}

int clock_getres(clockid_t clk_id, struct timespec *res){
	
	return;
}

ssize_t read(int fd, void *buf, size_t count){
	
	return;
}

int fcntl(int fd, int cmd, ... /* arg */ ){
	
	return;
}

int select(int nfds, struct fd_set *readfds, struct fd_set *writefds,
                 struct fd_set *exceptfds, struct timeval *timeout){
	
	return;
}

int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen){
	
	return;
}

off_t lseek(int fd, off_t offset, int whence){
	
	return;
}

int lstat64(const char *pathname, struct stat64 *buf){

	return;
}

int stat64(const char *pathname, struct stat64 *buf){

	return;
}

int fstat64(int fildes, struct stat64 *buf){
	
	return;
}

char *getcwd(char *buf, size_t size){

	return;
}

void *mmap(void *addr, size_t length, int prot, int flags,
                  int fd, off_t offset){
	
	return;
}

int sprintf(char *result, const char *format, ...){
	
	return;
}

#if defined(__cplusplus)
}
#endif
          
