-----------------------------------------
How to Build/Execute your own Python Code
-----------------------------------------
#### 1. Install Intel(R) SGX SDK for Linux* OS.
* Download SGX Driver, SGX PSW, SGX SDK from https://download.01.org/intel-sgx/linux-2.2/ubuntu64-server/, Install them. 
#### 2. Install pypy and libffi for your machine.
* Download pypy by using "sudo apt-get install" command in Linux machine.
* Download libffi from https://github.com/libffi/libffi, Build libffi.a following the instructions. 
####Notice:You will find library under libffi/x86_64-unknown-linux-gnu/.libs/libffi.a 
#### 3. Download pypy package provided by us.
* Download MesaPy from our github MesaPy, choose sgx branch.
* Download MesaPy from our github MesaPy, choose mesapy2.7 branch.
#### 4. Build project following the detail instructions we provide below:
* Build libpypy-c.a by using the pypy source code in MesaPy sgx branch. 
>* Go into mesapy/pypy/goal directory
>* Run command "../../rpython/bin/rpython --opt=2 targetstandaloned.py --no-allworkingmodules"
>* The libpypy-c.a will be generated and you can find it in tmp directory shown in the terminal or you can set your own path for it.
>* Copy the whole content of ussesion folder to where you want, usually under Enclave directory as Samples do.
    
* Build Python functions' C interfaces using CFFI.
>* you can write your own code following the sample code. 
>>* Write your own Python function code you want to call in Enclave in implementation.py.
>>* Write cffi interface generating part in embed.py. Notice: Import the CFFI library provided by us.
>>* Write your function's C interface defition in api.h.
>* Download MesaPy, replace lib-pypy and lib_python folders with provided by sgx-wip, which let "import cffi" use lib_pypy and lib-python we provid, also download the inlcude folder and typedefine.h.
>* Run pypy ./embed.py for generating the corresponed object file.

* Write your own edl for your ecall function, see sample in Sample directory.

* Write your own Makefile, link libpypy-c.a, libffi.a and Python C interface function's object file in Enclave.so, you can do these by referring Makefile provided by Sample code. 

* Run "make" to generate sgx binary app.
	
* Run ./app. Here you go!

#### NOTICE: While running pypy embed.py, make sure the typedefine.h and PyPy header include directory are in the parent directory as the command running, and import the cffi module from the lib_pypy we provide.

