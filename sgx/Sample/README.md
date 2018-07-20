
------------------------------------
How to Build/Execute the Sample Code
------------------------------------
#### 1. Install Intel(R) SGX SDK for Linux* OS.
* Download SGX driver, SGX PSW, SGX SDK from https://download.01.org/intel-sgx/linux-2.2/ubuntu64-server/, Install them. 
#### 2. Install pypy and libffi for your machine.
* Download pypy using sudo apt-get install command in Linux machine
* Download libffi from https://github.com/libffi/libffi, Build libffi.a by following the instruction in libffi, You will find library under libffi/x86_64-unknown-linux-gnu/.libs/libffi.a.
#### 3. Download pypy package provided by us.
* Download MesaPy from our github MesaPy, choose sgx branch.
#### 4. Build project as the detail instruction we provide in the following:
* Build libpypy-c.a by using the pypy source code in MesaPy sgx branch.
>* Go into pypy/pypy/goal directory
>* Run command "../../rpython/bin/rpython --opt=2 targetstandaloned.py --no-allworkingmodules"
>* The libpypy-c.a will be generated and you can find it in tmp directory showing in the terminal or you can set your own path for it.

* Build Python functions' C interfaces using CFFI.
>* The example code is under /Enclave/pypy_embedding, there are files, implementation.py, embed.py, api.h
>* run pypy ./embed.py for generating the corresponed object file.

* Copy whole ussesion folder content from step 1 to usession folder under directory Enclave, Copy libffi to libffi-3.0.13 folder under directory Enclave.

* Run "make" in the Sample/Compute(HelloWorld, Exec), which generates sgx binary app.

* Make sure SGX service is started on your machine. 

* Run ./app. Here you go!

#### NOTICE: While running pypy embed.py, make sure the typedefine.h and include directory are in the parent directory as the command running, and import the cffi module from the lib_pypy we provide.


