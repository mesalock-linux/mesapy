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


#define __FD_SETSIZE 1024
#define __NFDBITS (8 * sizeof(unsigned long))
#define __FDSET_LONGS (__FD_SETSIZE/__NFDBITS)
struct fd_set{
  unsigned long fds_bits[__FDSET_LONGS];
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

//#define int fprintf_sgx(int stream, const char *format, ...)
#define fprintf()
#define stderr 2 
