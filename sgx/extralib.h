
#define PATH_MAX 4096


#define READ 0
#define WRITE 1
#define OPEN 2
#define CLOSE 3
#define STAT 4
#define FSTAT 5
#define LSTAT 6
#define POLL 7
#define LSEEK 8
#define MMAP 9
#define IOCTL 16
#define READV 19
#define WRITEV 20
#define ACCESS 21
#define SELECT 23
#define DUP2 33
#define NANOSLEEP 35
#define SOCKET 41
#define CONNECT 42
#define ACCEPT 43
#define SENDTO 44
#define RECVFROM 45
#define SENDMSG 46
#define RECVMSG 47
#define SHUTDOWN 48
#define BIND 49
#define LISTEN 50
#define GETSOCKNAME 51
#define GETPEERNAME 52
#define SOCKETPAIR 53
#define SETSOCKOPT 54
#define GETSOCKOPT 55
#define CLONE 56
#define FORK 57
#define VFORK 58
#define EXECVE 59
#define WAIT4 61
#define FCNTL 72
#define GETCWD 79
#define CHDIR 80
#define UNLINK 87
#define READLINK 89
#define GETSID 124
#define GETDENTS 217
#define CLOCK_GETTIME 228
#define CLOCK_GETRES 229
#define EXIT_GROUP 231
#define PIPE 293
# define _SIGSET_NWORDS (1024 / (8 * sizeof (unsigned long int)))


unsigned long open(long pathname, long flags, long mode);
unsigned long open2(long pathname, long flags);
unsigned long close(long fd);
unsigned long unlink(long pathname);
unsigned long readlink(long path, long buf, long bufsiz);
unsigned long access(long pathname, long mode);
unsigned long readv(long fd, long iov, long iovcnt);
unsigned long writev(long fd, long iov, long iovcnt);
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
char* getcwd(char* buf, long size);
unsigned long mmap(long addr, long length, long port, long flags, long fd, long offset);
int sprintf(char *result, const char *format, ...);
void ocall_printf(const char *fmt, ...);



struct sigset_t
  {
    unsigned long int __val[_SIGSET_NWORDS];
  };

struct sched_param
  {
    int __sched_priority;
  };

struct __spawn_action
 {
   enum
   {
     spawn_do_close,
     spawn_do_dup2,
     spawn_do_open
   } tag;

   union
   {
     struct
     {
       int fd;
     } close_action;
     struct
     {
       int fd;
       int newfd;
     } dup2_action;
     struct
     {
       int fd;
       const char *path;
       int oflag;
       int mode;
     } open_action;
   } action;
 };


struct posix_spawnattr_t
{
  short int __flags;
  int __pgrp;
  struct sigset_t __sd;
  struct sigset_t __ss;
  struct sched_param __sp;
  int __policy;
  int __pad[16];
} ;

struct posix_spawn_file_actions_t
{
  int __allocated;
  int __used;
  struct __spawn_action *__actions;
  int __pad[16];
} ;

struct args {
        int p[2];
        struct sigset_t oldmask;
        const char *path;
        int (*exec)(const char *, char *const *, char *const *);
        const struct posix_spawn_file_actions_t *fa;
        const struct posix_spawnattr_t * attr;
        char *const *argv, *const *envp;
};

struct args *arg_global;
typedef int (*func_ptr)(void*);
func_ptr childfunc_addr;

struct iovec {
        void *iov_base;
        unsigned long iov_len;
};

struct timespec {
        long tv_sec;
        long tv_nsec;
};

struct enclave_sockaddr {
        long sa_family;
        char sa_data[14];
};

struct timeval {
               long    tv_sec;         /* seconds */
               long    tv_usec;        /* microseconds */
           };


#define __FD_SETSIZE 1024
#define __NFDBITS (8 * sizeof(unsigned long))
#define __FDSET_LONGS (__FD_SETSIZE/__NFDBITS)
struct enclave_fd_set{
  unsigned long fds_bits[__FDSET_LONGS];
};

struct enclave_pollfd {
               int   fd;         /* file descriptor */
               short events;     /* requested events */
               short revents;    /* returned events */
           };

//struct msghdr {
//    void         *msg_name;       /* optional address */
//    socklen_t     msg_namelen;    /* size of address */
//    struct iovec *msg_iov;        /* scatter/gather array */
//    size_t        msg_iovlen;     /* # elements in msg_iov */
//    void         *msg_control;    /* ancillary data, see below */
//    size_t        msg_controllen; /* ancillary data buffer len */
//    int           msg_flags;      /* flags on received message */
//};



struct stat
  {
    unsigned long st_dev;             /* Device.  */

   unsigned long st_ino;             /* File serial number.  */


   unsigned long st_nlink;         /* Link count.  */
    unsigned int st_mode;           /* File mode.  */

    unsigned int st_uid;             /* User ID of the file's owner. */
    unsigned int st_gid;             /* Group ID of the file's group.*/

    int __pad0;

    long st_rdev;            /* Device number, if device.  */


    long st_size;                    /* Size of file, in bytes.  */

    long st_blksize;     /* Optimal block size for I/O.  */

    long st_blocks;               /* Number 512-byte blocks allocated. */


    /* Nanosecond resolution timestamps are stored in a format
       equivalent to 'struct timespec'.  This is the type used
       whenever possible but the Unix namespace rules do not allow the
       identifier 'timespec' to appear in the <sys/stat.h> header.
       Therefore we have to handle the use of this header in strictly
       standard-compliant sources special.  */
    struct timespec st_atim;            /* Time of last access.  */
    struct timespec st_mtim;            /* Time of last modification.  */
    struct timespec st_ctim;            /* Time of last status change.  */
# define st_atime st_atim.tv_sec        /* Backward compatibility.  */
# define st_mtime st_mtim.tv_sec
# define st_ctime st_ctim.tv_sec
    long int __glibc_reserved[3];


    unsigned long int __glibc_reserved4;
    unsigned long int __glibc_reserved5;

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


struct dirent {
        long d_ino;
        long d_off;
        unsigned short d_reclen;
        unsigned char d_type;
        char d_name[256];
};


struct rusage {
    struct timeval ru_utime; /* user CPU time used */
    struct timeval ru_stime; /* system CPU time used */
    long   ru_maxrss;        /* maximum resident set size */
    long   ru_ixrss;         /* integral shared memory size */
    long   ru_idrss;         /* integral unshared data size */
    long   ru_isrss;         /* integral unshared stack size */
    long   ru_minflt;        /* page reclaims (soft page faults) */
    long   ru_majflt;        /* page faults (hard page faults) */
    long   ru_nswap;         /* swaps */
    long   ru_inblock;       /* block input operations */
    long   ru_oublock;       /* block output operations */
    long   ru_msgsnd;        /* IPC messages sent */
    long   ru_msgrcv;        /* IPC messages received */
    long   ru_nsignals;      /* signals received */
    long   ru_nvcsw;         /* voluntary context switches */
    long   ru_nivcsw;        /* involuntary context switches */
};

struct Dl_info{
               const char *dli_fname;  /* Pathname of shared object that
                                          contains address */
               void       *dli_fbase;  /* Base address at which shared
                                          object is loaded */
               const char *dli_sname;  /* Name of symbol whose definition
                                          overlaps addr */
               void       *dli_saddr;  /* Exact address of symbol named
                                          in dli_sname */
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

#define fprintf()
