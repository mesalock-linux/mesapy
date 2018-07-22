### Verification Environment Setup

We provide the scripts to automatically evaluate RPython C backend programs. Dockerfile is provided to setupt the environment for user to verify Rpython C program. Beside, users can also download Seahorn and build from the source. The shellscripts we provided can be used to automatically generate bc and provide the seahorn verification. The output will be the verification results for each C program under /pypy/rpython/translator/c/src.

First step is to generator the image from dockerfile:
````shell
docker build -t /the/path/to/dockerfile . 
````

Then setupt the shellscript running environemt as following:
````shell
mkdir /pypy/rpython/translator/c/src/bc
cp cmd.sh /pypy/rpython/translator/c/src/
cp sh.sh /pypy/rpython/translator/c/src/
cd /pypy/rpython/translator/c/src/
./cmd.sh
````
The verification results will be in /pypy/RPython/translator/c/src/seahorn.results.

### Verification results 


| Filename      | Verified Result   | LOC  |
| ------------- |:-----------------:| ----:|
| asm.c         |     unsat         | 13   |
| asm_gcc_x86.c |     unsat         | 33   | 
| cygwin_wait.c |     unsat         | 59   | 
| asm_gcc_x86.c |     unsat         | 33   |
| asm_msvc.c    |     unsat         | 26   |
| debug_print.c |     sat           | 274  |
| dtoa.c        |     unsat         | 3006 |
| entrypoint.c  |     unsat         | 130  |
| exception.c   |     unsat         | 45   |
| instrument.c  |     unsat         | 76   |
| int.c         |     unsat         | 48   |
| ll_strtod.c   |     sat           | 145  |
| mem.c         |     sat           | 178  |
| profiling.c   |     sat           | 73   |
| rtyper.c      |     sat           | 38   |
| signals.c     |     sat           | 206  |
| stack.c       |     sat           | 66   |
| support.c     |     sat           | 27   |
| thread.c      |     sat           | 22   |
| threadlocal.c |     sat           | 273  |

### To Do List

The remaining C files to be verified are included as following:
````shell
/pypy/rpython/translator/c/src/libffi_msvc/pypy_ffi.c
/pypy/rpython/translator/c/src/libffi_msvc/prep_cif.c
/pypy/rpython/translator/c/src/libffi_msvc/win32.c
/pypy/rpython/translator/c/src/libffi_msvc/ffi.c
/pypy/rpython/translator/c/src/libffi_msvc/types.c
/pypy/rpython/jit/backend/llsupport/src/codemap.c
/pypy/rpython/jit/backend/llsupport/src/skiplist.c
/pypy/rpython/rlib/module_cache/module_22.c
/pypy/rpython/rlib/module_cache/module_23.c
/pypy/rpython/rlib/module_cache/module_24.c 
/pypy/rpython/rlib/module_cache/module_25.c 
/pypy/rpython/rlib/module_cache/module_26.c 
/pypy/rpython/rlib/module_cache/module_27.c 
/pypy/rpython/rlib/module_cache/module_28.c 
/pypy/rpython/rlib/module_cache/module_29.c 
/pypy/rpython/rlib/module_cache/module_30.c 
/pypy/rpython/rlib/module_cache/module_31.c 
/pypy/rpython/rlib/module_cache/module_32.c 
/pypy/rpython/rlib/module_cache/module_33.c 
/pypy/rpython/rlib/module_cache/module_34.c
````

