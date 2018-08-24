# Welcome to MesaPy in SGX

MesaPy SGX SDK aims at helping developers write Intel SGX applications in Python language with memory safety.

## Getting Started with Sample
### Requirement
* Ubuntu 16.04
* Support SGX, check the link(https://github.com/ayeks/SGX-hardware), find out if your machine has SGX support.  

### 1. Install Intel(R) SGX SDK for Linux* OS.
* Download SGX Driver, SGX PSW, SGX SDK from https://download.01.org/intel-sgx/linux-2.2/ubuntu64-server/, following link  (https://download.01.org/intel-sgx/linux-2.2/docs/Intel_SGX_Installation_Guide_Linux_2.2_Open_Source.pdf)install them. 
### 2. Install pypy and libffi for your machine.
* Install pypy by using "sudo apt-get install" command in Linux machine.
```
$ sudo apt-get install pypy
$ sudo apt-get install pypy-dev
```
* Download libffi from https://github.com/libffi/libffi, Build libffi.a and install libffi by following the instructions provided from the website.
#### Notice:You will find library under libffi/x86_64-unknown-linux-gnu/.libs/libffi.a.
### 3. Download pypy package provided by us.
* Download MesaPy from our github MesaPy, Choose sgx branch. Save in directory sgx.
```
$ git clone -b sgx git@github.com:mesalock-linux/mesapy.git
```
* Build MesaPy2.7 from source. Save MesaPy2.7 in directory mesapy2.7. The detailed steps are explained in the [documentation](https://docs.mesapy.org/building-from-source.html).

### 4. Build project as the detail instructions we provide in the following:
* Build libpypy-c.a by using the pypy source code in MesaPy sgx branch, Go into pypy/pypy/goal directory.
```
$ "../../rpython/bin/rpython --opt=2 targetstandaloned.py --no-allworkingmodules"
```
>* The libpypy-c.a will be generated and stored in the directory /pypy/pypy/goal/

* Build Python functions' C interfaces using CFFI.
>* The example code is under /Enclave/pypy_embedding. There are three files, implementation.py, embed.py, api.h.
>* Replace lib-pypy and lib_python folders in mesapy2.7 with provided by sgx-wip , which let "import cffi" use lib_pypy and lib-python we provide.
>* run mesapy2.7/mesapy/pypy/goal/pypy-c ./embed.py for generating the corresponed object file.

* Copy libpypy-c.a and libffi.a to directory Enclave.

* Run "make" in the Sample/Compute(HelloWorld, Exec), which generates sgx binary app.

* Make sure SGX service is started on your machine. 

* Run ./app. Here you go!
```
$
$
$
```

### NOTICE: While running pypy embed.py, make sure the typedefine.h and include directory are in the parent directory as the command running, and import the cffi module from the lib_pypy we provide.

## Customization 
* Write your own edl for your ecall function, see Getting Started with Sample.
* Write your own code following the sample code.
>* Write your own Python function code you want to call in Enclave in implementation.py.
>* Write cffi interface generating part in embed.py.
>* Write your function's C interface defition in api.h.
* Write your own Makefile, link libpypy-c.a, libffi.a and Python C interface function's object file in Enclave.so, you can do these by referring Makefile provided by Sample code.








