# define _SIGSET_NWORDS (1024 / (8 * sizeof (unsigned long int)))

struct sigset_t
  {
    unsigned long int __val[_SIGSET_NWORDS];
  };

struct timespec {
        long tv_sec;
        long tv_nsec;
};

struct sockaddr {
        long sa_family;
        char sa_data[14];
};

struct timeval {
               long    tv_sec;         /* seconds */
               long    tv_usec;        /* microseconds */
           };

struct stat64
  {
    unsigned long st_dev;             /* Device.  */
    unsigned long st_ino;           /* File serial number.  */
    unsigned long st_nlink;         /* Link count.  */
    unsigned int st_mode;           /* File mode.  */
    unsigned int st_uid;             /* User ID of the file's owner. */
    unsigned int st_gid;             /* Group ID of the file's group.*/

    int __pad0;
    long st_rdev;            /* Device number, if device.  */
    long st_size;            /* Size of file, in bytes.  */

    long st_blksize;     /* Optimal block size for I/O.  */
    long st_blocks;     /* Nr. 512-byte blocks allocated.  */

    struct timespec st_atim;            /* Time of last access.  */
    struct timespec st_mtim;            /* Time of last modification.  */
    struct timespec st_ctim;            /* Time of last status change.  */

    long int __glibc_reserved[3];

  };

 #define _UTSNAME_LENGTH 65 
 #ifndef _UTSNAME_SYSNAME_LENGTH
 # define _UTSNAME_SYSNAME_LENGTH _UTSNAME_LENGTH
 #endif
 #ifndef _UTSNAME_NODENAME_LENGTH
 # define _UTSNAME_NODENAME_LENGTH _UTSNAME_LENGTH
 #endif
 #ifndef _UTSNAME_RELEASE_LENGTH
 # define _UTSNAME_RELEASE_LENGTH _UTSNAME_LENGTH
 #endif
 #ifndef _UTSNAME_VERSION_LENGTH
 # define _UTSNAME_VERSION_LENGTH _UTSNAME_LENGTH
 #endif
 #ifndef _UTSNAME_MACHINE_LENGTH
 # define _UTSNAME_MACHINE_LENGTH _UTSNAME_LENGTH
 #endif
 
/* Structure describing the system and machine.  */
 struct utsname
   {
     /* Name of the implementation of the operating system.  */
     char sysname[_UTSNAME_SYSNAME_LENGTH];
 
     /* Name of this node on the network.  */
     char nodename[_UTSNAME_NODENAME_LENGTH];
 
     /* Current release level of this implementation.  */
     char release[_UTSNAME_RELEASE_LENGTH];
     /* Current version level of this release.  */
     char version[_UTSNAME_VERSION_LENGTH];
 
     /* Name of the hardware type the system is running on.  */
     char machine[_UTSNAME_MACHINE_LENGTH];
 
 #if _UTSNAME_DOMAIN_LENGTH - 0
     /* Name of the domain of this node on the network.  */
 # ifdef __USE_GNU
     char domainname[_UTSNAME_DOMAIN_LENGTH];
 # else
     char __domainname[_UTSNAME_DOMAIN_LENGTH];
 # endif
 #endif
   };

struct lconv
{
  /* Numeric (non-monetary) information.  */

  char *decimal_point;          /* Decimal point character.  */
  char *thousands_sep;          /* Thousands separator.  */
  /* Each element is the number of digits in each group;
     elements with higher indices are farther left.
     An element with value CHAR_MAX means that no further grouping is done.
     An element with value 0 means that the previous element is used
     for all groups farther left.  */
  char *grouping;

  /* Monetary information.  */

  /* First three chars are a currency symbol from ISO 4217.
     Fourth char is the separator.  Fifth char is '\0'.  */
  char *int_curr_symbol;
  char *currency_symbol;        /* Local currency symbol.  */
  char *mon_decimal_point;      /* Decimal point character.  */
  char *mon_thousands_sep;      /* Thousands separator.  */
  char *mon_grouping;           /* Like `grouping' element (above).  */
  char *positive_sign;          /* Sign for positive values.  */
  char *negative_sign;          /* Sign for negative values.  */
  char int_frac_digits;         /* Int'l fractional digits.  */
  char frac_digits;             /* Local fractional digits.  */
  /* 1 if currency_symbol precedes a positive value, 0 if succeeds.  */
  char p_cs_precedes;
  /* 1 iff a space separates currency_symbol from a positive value.  */
  char p_sep_by_space;
  /* 1 if currency_symbol precedes a negative value, 0 if succeeds.  */
  char n_cs_precedes;
  /* 1 iff a space separates currency_symbol from a negative value.  */
  char n_sep_by_space;
  /* Positive and negative sign positions:
     0 Parentheses surround the quantity and currency_symbol.
     1 The sign string precedes the quantity and currency_symbol.
     2 The sign string follows the quantity and currency_symbol.
     3 The sign string immediately precedes the currency_symbol.
     4 The sign string immediately follows the currency_symbol.  */
  char p_sign_posn;
  char n_sign_posn;
#ifdef __USE_ISOC99
  /* 1 if int_curr_symbol precedes a positive value, 0 if succeeds.  */
  char int_p_cs_precedes;
  /* 1 iff a space separates int_curr_symbol from a positive value.  */
  char int_p_sep_by_space;
  /* 1 if int_curr_symbol precedes a negative value, 0 if succeeds.  */
  char int_n_cs_precedes;
  /* 1 iff a space separates int_curr_symbol from a negative value.  */
  char int_n_sep_by_space;
  /* Positive and negative sign positions:
     0 Parentheses surround the quantity and int_curr_symbol.
     1 The sign string precedes the quantity and int_curr_symbol.
     2 The sign string follows the quantity and int_curr_symbol.
     3 The sign string immediately precedes the int_curr_symbol.
     4 The sign string immediately follows the int_curr_symbol.  */
  char int_p_sign_posn;
  char int_n_sign_posn;
#else
  char __int_p_cs_precedes;
  char __int_p_sep_by_space;
  char __int_n_cs_precedes;
  char __int_n_sep_by_space;
  char __int_p_sign_posn;
  char __int_n_sign_posn;
#endif
};

#define __fd_mask long
#define __NFDBITS       (8 * (int) sizeof (__fd_mask))
#define __FD_SETSIZE 1024
struct fd_set
{
    /* XPG4.2 requires this member name.  Otherwise avoid the name
       from the global namespace.  */
#ifdef __USE_XOPEN
    __fd_mask fds_bits[__FD_SETSIZE / __NFDBITS];
# define __FDS_BITS(set) ((set)->fds_bits)
#else
    __fd_mask __fds_bits[__FD_SETSIZE / __NFDBITS];
# define __FDS_BITS(set) ((set)->__fds_bits)
#endif
};


#define off_t long
#define size_t long
#define ssize_t long
#define mode_t int
#define socklen_t int
#define clockid_t int

int dlclose(void * handle);
void *dlopen(const char* filename, int flag);
char *dlerror(void);
void *dlsym(void *handle, const char *symbol);
int isatty(int fd);
int ftruncate(int fd, long length);
int uname(struct utsname *buf);
int madvise(void *addr, size_t length, int advice);
char *setlocale(int category, const char *locale);
char *nl_langinfo(int item);
struct lconv *localeconv(void);
int execv(const char *path, char *const argv[]);
char *getenv(const char *name);
long syscall(long number, ...);
int fork(void);
int mprotect(void *addr, size_t len, int prot);
int prctl(int option, unsigned long arg2, unsigned long arg3,
                 unsigned long arg4, unsigned long arg5);
void _exit(int status);
void setbuf(void *stream, char *buf);
int fclose(void* stream);
void *fdopen(int fd, const char *mode);
int open(const char *pathname, int flags, mode_t mode);
int close(int fd);
int unlink(const char *pathname);
ssize_t readlink(const char *pathname, char *buf, size_t bufsiz);
int access(const char *pathname, int mode);
int clock_gettime(clockid_t clk_id, struct timespec *tp);
int clock_getres(clockid_t clk_id, struct timespec *res);
ssize_t read(int fd, void *buf, size_t count);
int fcntl(int fd, int cmd, ... /* arg */ );
int select(int nfds, struct fd_set *readfds, struct fd_set *writefds,
                  struct fd_set *exceptfds, struct timeval *timeout);
int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
off_t lseek(int fd, off_t offset, int whence);
int lstat64(const char *pathname, struct stat64 *buf);
int stat64(const char *pathname, struct stat64 *buf);
int fstat64(int fildes, struct stat64 *buf);
char *getcwd(char *buf, size_t size);
void *mmap(void *addr, size_t length, int prot, int flags,
                  int fd, off_t offset);
int sprintf(char *result, const char *format, ...);

