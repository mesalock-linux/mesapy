# MesaPy for SGX

MesaPy for SGX aims at helping developers to write memory-safe Intel SGX apps in
Python.

## Getting Started

### Requirements

MesaPy for SGX needs following hardware requirements to run SGX:

- CPU with Intel SGX support (6th Generation Intel Core Processor or newer, you
  can check in the [list of SGX supported hardware](https://github.com/ayeks/SGX-hardware))
- Intel SGX option enabled in BIOS

Also, ensure that you have one of the follwing operating systems required by SGX:

- Ubuntu 16.04.3 LTS 64-bit Desktop version
- Ubuntu 16.04.3 LTS 64-bit Server version
- Red Hat Enterprise Linux Server release 7.4 64bits
- CentOS 7.4.1708 64bits
- SUSE Linux Enterprise Server 12 64bits

Below, we use Ubuntu 16.04.3 as an example to show steps to get started with
MesaPy for SGX.

### Installing Intel SGX

Let's install dependencies for Instal SGX PSW and SGX SDK first. Following instructions are
for Ubuntu 16.04, you can find detailed guilde from
the [Intel SGX Installation Guide](https://download.01.org/intel-sgx/linux-2.2/docs/Intel_SGX_Installation_Guide_Linux_2.2_Open_Source.pdf).

```
# Install dependencies of Intel SGX PSW:
$ sudo apt-get install libssl-dev libcurl4-openssl-dev libprotobuf-dev

# Install dependencies of Intel SGX SDK
$ sudo apt-get install build-essential python

# Install trusted platform service
# Download Capability Licensing Client (iCLS) for Linux 64-bit clinet from https://software.intel.com/en-us/sgx-sdk/download
$ sudo apt-get install alien
$ sudo alien --scripts iclsClient-1.45.449.12-1.x86_64.rpm
$ sudo dpkg -i iclsclient_1.45.449.12-2_amd64.deb

# Download dynamic-application-loader-host-interface from https://github.com/intel/dynamic-application-loader-host-interface
# Install dependencies
$ sudo apt-get install uuid-dev libxml2-dev cmake pkg-config
$ cmake .; make; sudo make install;sudo systemctl enable jhi
```

Then, let's install driver, PSW packages and SDK. First, download them from
[https://download.01.org/intel-sgx/linux-2.2/](https://download.01.org/intel-sgx/linux-2.2/).
Then, follow these instructions to install.

```
$ sudo ./sgx_linux_x64_driver.bin
$ sudo ./sgx_linux_<os>_x64_psw_<version>.bin
$ sudo ./sgx_linux_<os>_x64_sdk_<version>.bin
```

### Building MesaPy for SGX

Install dependencies described in the [documentation](https://docs.mesapy.org/building-from-source.html#install-dependencies).

```
$ sudo apt-get install gcc make libffi-dev pkg-config libgdbm-dev libgc-dev python-cffi
```

Clone MesaPy from GitHub. Note that currently MesaPy for SGX is in the `sgx` branch.

```
$ git clone -b sgx git@github.com:mesalock-linux/mesapy.git
```

Build MesaPy for SGX:

```
$ cd pypy/goal
$ ../../rpython/bin/rpython --opt=2 targetpypystandalone.py --no-allworkingmodules
```

The detailed instructions of building MesaPy are described in the
[documentation](https://docs.mesapy.org/building-from-source.html**.

**TODO: all things below need to be polished, will come back later.**

### Run examples

### Build libffi

Clone libffi from GitHub.

```
$ git clone https://github.com/libffi/libffi
```

Build libffi.a and install libffi by following the instructions provided from the website.

#### Notice:You will find library under libffi/x86_64-unknown-linux-gnu/.libs/libffi.a.

>* The libpypy-c.a will be generated and stored in the directory /pypy/pypy/goal/

* Build Python functions' C interfaces using CFFI.
>* The example code is under /Enclave/pypy_embedding. There are three files, implementation.py, embed.py, api.h.
>* Replace lib-pypy and lib_python folders in mesapy2.7 with provided by sgx-wip , which let "import cffi" use lib_pypy and lib-python we provide.
>* run mesapy2.7/mesapy/pypy/goal/pypy-c ./embed.py for generating the corresponed object file.

* Copy libpypy-c.a and libffi.a to directory Enclave.

* Run "make" in the Sample/Compute(HelloWorld, Exec), which generates sgx binary app.

* Make sure SGX service is started on your machine. 

* Run ./app. Here you go! You will expect the following result from Compute. Exec, HelloWorld.
```
$ ret_compute is 6 
$ helloworld
$ helloworld. this line will be printed!
```

### NOTICE: While running pypy embed.py, make sure the typedefine.h and include directory are in the parent directory as the command running, and import the cffi module from the lib_pypy we provide.

## Customization 
* Write your own edl for your ecall function, see Getting Started with Sample.
* Write your own code following the sample code.
>* Write your own Python function code you want to call in Enclave in implementation.py.
>* Write cffi interface generating part in embed.py.
>* Write your function's C interface defition in api.h.
* Write your own Makefile, link libpypy-c.a, libffi.a and Python C interface function's object file in Enclave.so, you can do these by referring Makefile provided by Sample code.
* Have SGX heap size as 2M.
