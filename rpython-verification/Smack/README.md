## System Requirements and Installation


We can run SMACK on standard Ubuntu. Below we outline system requirements and installation instructions for typical system configurations.

### Super-Quick Setup: Smack

Just download Smack (https://github.com/smackers/smack) and build from source, or you can use a preconfigured virtual environment using Vagrant and VirtualBox, which has been released in Smack website. Here we only show the instructions to evaluate rpython backend by using the preconfigured one. 


### Quick Setup: Vagrant Development Environment

We follow the following two commands to start the preconfigured virtual machine with Smack in SMACK.s root directory (that which contains `Vagrantfile`):
````Shell
vagrant up
vagrant ssh
````

### General System Requirements

Rpython C backend verification depends on the following projects:

* [LLVM] version [3.9.1][LLVM-3.9.1]
* [Clang] version [3.9.1][Clang-3.9.1]
* [Python] version 2.7 or greater
* [Mono] version 5.0.0 or greater (except on Windows)
* [Z3] or compatible SMT-format theorem prover
* [Boogie] or [Corral] or compatible Boogie-format verifier
* [PyPy] version 2.7 or greater
* [wllvm] pip version 

### Installation on Linux

Smack can work on C program and LLVM bitcode. To facilitate the Rpython verification, we provide an automated [build.sh][] script in `bin/build.sh`. However, we do not expect this script to work out of the box on all configurations. Instead, it can be used as reference guidelines for manual installation.


### Installing SMACK Itself

SMACK is built using [CMake][] via the following sequence of shell commands
from SMACK.s root directory:
````Shell
mkdir build
cd build
cmake -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_BUILD_TYPE=Debug ..
make install
````
Note that the `llvm-config` binary must be in your executable `PATH`.
To specify an install location `PREFIX` other than the default installation
prefix, add the additional flag:
````Shell
-DCMAKE_INSTALL_PREFIX=PREFIX
````
substituting the string `PREFIX` for the desired location.

Actually running SMACK relies on the environment variables `BOOGIE` and
`CORRAL` targeting the `Boogie.exe` and `corral.exe` executables, for instance
residing in paths prefixed by `XXX` and `YYY`:
````Shell
export BOOGIE="mono /XXX/Boogie/Binaries/Boogie.exe"
export CORRAL="mono /YYY/Corral/bin/Release/corral.exe"
````
Source the preceding lines in your shell.s `.profile`, and ensure they invoke
Boogie/Corral correctly. For example, running
````Shell
BOOGIE
````
should result in
````
*** Error: No input files were specified.
````
printed to standard output.

Finally, note that the following LLVM and Clang binaries must be in your
executable path: `clang`, `llvm-config`, `llvm-link`.

### Verification results


### To Do List

[Vagrant]: https://www.vagrantup.com
[VirtualBox]: https://www.virtualbox.org
[Python]: http://www.python.org
[LLVM-3.9.1]: http://llvm.org/releases/download.html#3.9.1
[Clang-3.9.1]: http://llvm.org/releases/download.html#3.9.1
[Boogie]: https://github.com/boogie-org/boogie
[Corral]: https://corral.codeplex.com/
[Z3]: https://github.com/Z3Prover/z3/
[wllvm]: https://github.com/travitch/whole-program-llvm
[pypy]: https://bitbucket.org/pypy/pypy/src