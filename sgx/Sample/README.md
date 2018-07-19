
------------------------------------
How to Build/Execute the Sample Code
------------------------------------
#### 1. Install Intel(R) SGX SDK for Linux* OS.
	1) Download SGX driver, SGX PSW, SGX SDK from https://download.01.org/intel-sgx/linux-2.2/ubuntu64-server/, Install them. 
#### 2. Install pypy and libffi for your machine.
	1)Download pypy using sudo apt-get install command in Linux machine
	2)Download libffi from https://github.com/libffi/libffi, following the instruction, generate libffi.a. Find library under libffi/x86_64-unknown-linux-gnu/.libs/libffi.a 
#### 3. Download pypy package provided by us.
	Download MesaPy from our github.
#### 4. Build project as the detail instruction we provide in the following:
	1) Build libpypy-c.a by using the pypy source code we provide. 
		a. Go into pypy/pypy/goal directory
                b. Run command "../../rpython/bin/rpython --opt=2 targetstandaloned.py --no-allworkingmodules"
                   The libpypy-c.a will be generated and put in tmp directory showing in the terminal or you can set path for it. 

        2) Build Python functions' C interfaces using CFFI.
		a. The example code is under /Enclave/pypy_embedding, there are files, implementation.py, embed.py, api.h
		b. run pypy ./embed.py for generating the corresponed object file.

	3) Copy ussesion directory from step 1 to usession under Enclave, copy libffi to libffi-3.0.13.

	5) Run "make" in the Sample/Compute(HelloWorld, Exec), which generates sgx binary app.
	
	6) Run ./app. Here you go!

#### NOTICE: While running pypy embed.py, make sure the typedefine.h and include directory are in the same directory as the command running, and import the cffi module from the lib_pypy we provide.


