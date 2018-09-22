FROM ubuntu:16.04
MAINTAINER Mingshen Sun <mssun@baidu.com>

ARG UID=1000
ARG GID=1000

RUN apt-get update

# Install dependencies of MesaPy for SGX:
RUN apt-get install -q -y --no-install-recommends \
        sudo \
        pypy \
        pypy-dev \
        gcc \
        make \
        libffi-dev \
        pkg-config \
        libgdbm-dev \
        libgc-dev \
        python-cffi

RUN groupadd -g ${GID} user && \
    useradd --create-home -u ${UID} -g ${GID} -s /bin/bash user && \
    adduser user sudo && \
    echo '%sudo ALL=(ALL) NOPASSWD:ALL' >> /etc/sudoers


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
    wget -O /root/sgx/psw.bin https://download.01.org/intel-sgx/linux-2.2/ubuntu64-desktop/sgx_linux_x64_psw_2.2.100.45311.bin && \
    wget -O /root/sgx/sdk.bin https://download.01.org/intel-sgx/linux-2.2/ubuntu64-desktop/sgx_linux_x64_sdk_2.2.100.45311.bin && \
    cd /root/sgx && \
    chmod +x /root/sgx/psw.bin && \
    /root/sgx/psw.bin && \
    chmod +x /root/sgx/sdk.bin && \
    echo -e 'no\n/opt' | /root/sgx/sdk.bin && \
    echo 'source /opt/sgxsdk/environment' >> /home/user/.bashrc && \
    rm -rf /root/sgx

# A script to run the AESM service
RUN echo "#!/bin/bash\n" >> /start_aesm_service.sh && \
    echo "source /opt/sgxsdk/environment" >> /start_aesm_service.sh && \
    echo "/opt/intel/sgxpsw/aesm/aesm_service &" >> /start_aesm_service.sh && \
    chmod u+x /start_aesm_service.sh

USER user
ENV USER=user

ENTRYPOINT sudo /start_aesm_service.sh && /bin/bash
