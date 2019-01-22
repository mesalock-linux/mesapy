FROM ubuntu:16.04
MAINTAINER Mingshen Sun <mssun@baidu.com>

RUN apt-get update

# Install dependencies of MesaPy for SGX:
RUN apt-get install -q -y --no-install-recommends \
        pypy \
        pypy-dev \
        gcc \
        make \
        automake \
        libltdl-dev \
        libtool \
        texinfo \
        libffi-dev \
        pkg-config \
        libgdbm-dev \
        libgc-dev \
        python-cffi

# Install dependencies of Intel SGX PSW:
RUN apt-get install -q -y --no-install-recommends \
        libssl-dev \
        libcurl4-openssl-dev \
        libprotobuf-dev

# Install dependencies of Intel SGX SDK
RUN apt-get install -q -y --no-install-recommends \
        build-essential \
        python

# Install other misc utils
RUN apt-get install -q -y --no-install-recommends \
        wget \
        ca-certificates \
        openssl \
        kmod

# Install Intel SGX PSW/SDK
RUN mkdir /root/sgx && \
    wget -O /root/sgx/psw.deb https://download.01.org/intel-sgx/linux-2.4/ubuntu16.04-server/libsgx-enclave-common_2.4.100.48163-xenial1_amd64.deb && \
    wget -O /root/sgx/sdk.bin https://download.01.org/intel-sgx/linux-2.4/ubuntu16.04-server/sgx_linux_x64_sdk_2.4.100.48163.bin && \
    wget -O /root/sgx/psw_dev.deb https://download.01.org/intel-sgx/linux-2.4/ubuntu16.04-server/libsgx-enclave-common-dev_2.4.100.48163-xenial1_amd64.deb && \
    cd /root/sgx && \
    dpkg -i psw.deb && \
    dpkg -i psw_dev.deb && \
    chmod +x /root/sgx/sdk.bin && \
    echo -e 'no\n/opt' | /root/sgx/sdk.bin && \
    echo 'source /opt/sgxsdk/environment' >> /root/.bashrc && \
    rm -rf /root/sgx

# A script to run the AESM service
RUN echo "#!/bin/bash\n" >> /start_aesm_service.sh && \
    echo "source /opt/sgxsdk/environment" >> /start_aesm_service.sh && \
    echo "/opt/intel/libsgx-enclave-common/aesm/aesm_service &" >> /start_aesm_service.sh && \
    chmod u+x /start_aesm_service.sh
