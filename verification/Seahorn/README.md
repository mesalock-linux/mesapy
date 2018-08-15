### Verification Environment Setup

We provide the scripts to automatically evaluate RPython translator/JIT backend programs.
Dockerfile is provided to setup the environment for user to verify RPython C
program. Beside, users can also download Seahorn and build from the source. The
shellscripts we provided can be used to automatically generate bc and provide
the seahorn verification. The output will be the verification results for each C
program under `/mesapy/rpython/translator/c/src`.

First step is to generator the image from dockerfile:

```
$ docker build -t /the/path/to/dockerfile .
```

Then setupt the shellscript running environemt as following:

```
$ mkdir /mesapy/rpython/translator/c/src/bc
$ cp cmd.sh /mesapy/rpython/translator/c/src/
$ cp sh.sh /mesapy/rpython/translator/c/src/
$ cd /mesapy/rpython/translator/c/src/
$ ./cmd.sh
```
The verification results will be in `/pypy/RPython/translator/c/src/seahorn.results`.

### Verification results

This table briefly illustrate our verification results. "sat" means that there exists
the violation of rules the memory safety rules. "unsat" means that no violation
of memory safety checking.

| Filename        |        Result       |   LOC |       Verified    |
| -------------   | :-----------------: | ----: | -----------------:|
| `asm.c`         | unsat               |    13 | :heavy_check_mark:|
| `asm_gcc_x86.c` | unsat               |    33 | :heavy_check_mark:|
| `cygwin_wait.c` | unsat               |    59 | :heavy_check_mark:|
| `asm_gcc_x86.c` | unsat               |    33 | :heavy_check_mark:|
| `asm_msvc.c`    | unsat               |    26 | :heavy_check_mark:|
| `debug_print.c` | sat                 |   274 | :x:               |
| `dtoa.c`        | unsat               |  3006 | :heavy_check_mark:|
| `entrypoint.c`  | unsat               |   130 | :heavy_check_mark:|
| `exception.c`   | unsat               |    45 | :heavy_check_mark:|
| `instrument.c`  | unsat               |    76 | :heavy_check_mark:|
| `int.c`         | unsat               |    48 | :heavy_check_mark:|
| `ll_strtod.c`   | sat                 |   145 | :x:               |
| `mem.c`         | sat                 |   178 | :x:               |
| `profiling.c`   | sat                 |    73 | :x:               |
| `rtyper.c`      | sat                 |    38 | :x:               |
| `signals.c`     | sat                 |   206 | :x:               |
| `stack.c`       | sat                 |    66 | :x:               |
| `support.c`     | sat                 |    27 | :x:               |
| `thread.c`      | sat                 |    22 | :x:               |
| `threadlocal.c` | sat                 |   273 | :x:               |

### To Do List

The remaining C files to be verified are included as following:

```
rpython/translator/c/src/libffi_msvc/pypy_ffi.c
rpython/translator/c/src/libffi_msvc/prep_cif.c
rpython/translator/c/src/libffi_msvc/win32.c
rpython/translator/c/src/libffi_msvc/ffi.c
rpython/translator/c/src/libffi_msvc/types.c
rpython/jit/backend/llsupport/src/codemap.c
rpython/jit/backend/llsupport/src/skiplist.c
${PYPY_USESSION_DIR}/module_cache/module_22.c
${PYPY_USESSION_DIR}/module_cache/module_23.c
${PYPY_USESSION_DIR}/module_cache/module_24.c
${PYPY_USESSION_DIR}/module_cache/module_25.c
${PYPY_USESSION_DIR}/module_cache/module_26.c
${PYPY_USESSION_DIR}/module_cache/module_27.c
${PYPY_USESSION_DIR}/module_cache/module_28.c
${PYPY_USESSION_DIR}/module_cache/module_29.c
${PYPY_USESSION_DIR}/module_cache/module_30.c
${PYPY_USESSION_DIR}/module_cache/module_31.c
${PYPY_USESSION_DIR}/module_cache/module_32.c
${PYPY_USESSION_DIR}/module_cache/module_33.c
${PYPY_USESSION_DIR}/module_cache/module_34.c
```
