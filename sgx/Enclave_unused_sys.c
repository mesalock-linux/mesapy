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

#if defined(__cplusplus)
}
#endif
          
