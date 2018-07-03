/* This optional file only works for GCC on an i386.
 * It replaces some complex macros with native assembler instructions.
 */

#include <stdio.h>
#include <stdlib.h>
#include <extralib.h>

#  ifdef PYPY_X86_CHECK_SSE2
void pypy_x86_check_sse2(void)
{
    //Read the CPU features.
    int features;
    asm("movl $1, %%eax\n"
        "pushl %%ebx\n"
        "cpuid\n"
        "popl %%ebx\n"
        "movl %%edx, %0"
        : "=g"(features) : : "eax", "edx", "ecx");
    
    //Check bits 25 and 26, this indicates SSE2 support
    if (((features & (1 << 25)) == 0) || ((features & (1 << 26)) == 0))
    {
	fprintf();
        abort();
    }
}
#  endif
