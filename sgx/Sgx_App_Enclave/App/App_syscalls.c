#if defined(__cplusplus)
extern "C" {
#endif

unsigned long ocall_syscall3(long n, long a1, long a2, long a3)
{
        unsigned long ret;

        __asm__ __volatile__ ("syscall" : "=a"(ret) : "a"(n), "D"(a1), "S"(a2),
                                                  "d"(a3) : "rcx", "r11", "memory");

        return ret;
}

#if defined(__cplusplus)
}
#endif
