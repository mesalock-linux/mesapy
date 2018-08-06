## System Requirements and Installation

We can run SMACK on standard Ubuntu. Below we outline system requirements and
installation instructions for typical system configurations.

### Smack Installation

Just download Smack (https://github.com/smackers/smack) and build from source,
or you can use a preconfigured virtual environment using Vagrant and VirtualBox,
which has been released in Smack website. Here we only show the instructions to
evaluate RPython backend by using the preconfigured one.

### Vagrant Development Environment

We follow the following two commands to start the preconfigured virtual machine
with Smack in SMACK.s root directory (that which contains `Vagrantfile`):

```
$ vagrant up
$ vagrant ssh
```

### General System Requirements

RPython C backend verification depends on the following projects:

* [LLVM][] version [3.9.1][LLVM-3.9.1]
* [Clang][] version [3.9.1][Clang-3.9.1]
* [Python][] version 2.7 or greater
* [Z3][] or compatible SMT-format theorem prover
* [Boogie][] or [Corral][] or compatible Boogie-format verifier
* [PyPy][] release-pypy2.7-v6.0.0
* [wllvm][] pip version 

### Verification Scripts

Smack can work on C program and LLVM bitcode. To facilitate the RPython
verification, we provide a Makefile to automatically generate bc for C files
under /pypy/rpython/traslator/c/src. However, we do not expect this script to
work out of the box on all configurations. Instead, it can be used as reference
guidelines for manual installation.

### Verification Steps

We need first download pypy and build it. Install wllvm before the verification
and follow below commands to generate bc for Smack verification

```
$ mkdir pypy
$ cd pypy
$ hg clone http://bitbucket.org/pypy/pypy pypy
$ cd pypy/pypy/pypy/goal
$ pypy ../../rpython/bin/rpython --opt=jit targetpypystandalone.py
```

After pypy built successfully, it will generate a fold `usession-default-xx` under `/tmp/`.

```
$ cp -r /usession-default-xx /home/vagrant/smack/examples/dataset/
$ cd pypy/rpython/traslator/c/src
$ cp Makefile .
$ make
```

Above commands can provide .o file for each C under
/pypy/rpython/traslator/c/src. We take int.c as an example:

```
$ export LLVM_COMPILER=clang
$ extract-bc int.o
$ smack -memory-safety int.o.bc
```

Please notice that smack relies on entry point for verification. We will write
the mock for each func in RPython C. ./mock provides all mocks we have wrote.

### Verification results 


| Filename        | Verified Result     |   LOC |     Verified      |
| -------------   | :-----------------: | ----: |-----------------: | 
| `dtoa.c`        | sat                 |  3006 | :x:               |    
| `asm_gcc_x86.c` | unsat               |    33 | :heavy_check_mark:| 
| `entrypoint.c`  | unsat               |   130 | :heavy_check_mark:| 
| `codemap.c`     | sat                 |   165 | :x:               |
| `skiplist.c`    | unsat               |   109 | :heavy_check_mark:|               |
| `debug_print.c` | unsat               |   274 | :heavy_check_mark:|
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
${USE_SESSION_DIR}/module_cache/module_22.c
${USE_SESSION_DIR}/module_cache/module_23.c
${USE_SESSION_DIR}/module_cache/module_24.c 
${USE_SESSION_DIR}/module_cache/module_25.c 
${USE_SESSION_DIR}/module_cache/module_26.c 
${USE_SESSION_DIR}/module_cache/module_27.c 
${USE_SESSION_DIR}/module_cache/module_28.c 
${USE_SESSION_DIR}/module_cache/module_29.c 
${USE_SESSION_DIR}/module_cache/module_30.c 
${USE_SESSION_DIR}/module_cache/module_31.c 
${USE_SESSION_DIR}/module_cache/module_32.c 
${USE_SESSION_DIR}/module_cache/module_33.c 
${USE_SESSION_DIR}/module_cache/module_34.c
```

[Python]: http://www.python.org
[LLVM]: http://llvm.org
[LLVM-3.9.1]: http://llvm.org/releases/download.html#3.9.1
[Clang]: http://clang.llvm.org
[Clang-3.9.1]: http://llvm.org/releases/download.html#3.9.1
[Boogie]: https://github.com/boogie-org/boogie
[Z3]: https://github.com/Z3Prover/z3/
[Xcode]: https://developer.apple.com/xcode/
[PyPy]: https://bitbucket.org/pypy/pypy
[wllvm]: https://github.com/travitch/whole-program-llvm
[Corral]: https://github.com/boogie-org/corral
