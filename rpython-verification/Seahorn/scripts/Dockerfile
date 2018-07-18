# Dockerfile for Seahorn

# OS image
FROM ubuntu:14.04

ENV SEAHORN=/home/seahorn/seahorn_bin
ENV PATH="/home/seahorn/seahorn/bin:$PATH"

# Install
RUN \
  sudo apt-get update -qq && \
  sudo apt-get upgrade -qq && \
  sudo apt-get install bridge-utils && \
  apt-get install -qq build-essential clang-3.6 && \
  apt-get install -qq software-properties-common && \
  apt-get install -qq curl git ninja-build man subversion vim wget cmake && \
  apt-get install -qq libboost-program-options-dev && \
  apt-get install python2.7 python2.7-dev -y && \
  apt-get install -y libboost1.55-all-dev && \
  apt-get install --yes libgmp-dev && \
  apt-get install --yes python-pip

RUN \
  export LZ="$TRAVIS_BUILD_DIR/../lz" && \
  mkdir -p $LZ && \
  wget --output-document=llvm-z3.tar.gz https://www.dropbox.com/s/cipjz38k3boyd1v/llvm-3.6-z3.tar.gz?dl=1 && \
  tar xvf llvm-z3.tar.gz -C $LZ && \
  ls $LZ && \
  sudo pip install lit && \
  sudo pip install OutputCheck


RUN \
  git clone https://github.com/seahorn/seahorn && \
  cd seahorn && \
  ls && \
  mkdir -p build && \
  cd build && \
  mv $LZ/run run && \
  /usr/bin/cmake -DBOOST_ROOT=$BOOST_ROOT -DZ3_ROOT=run -DLLVM_DIR=$(pwd)/run/share/llvm/cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_PROGRAM_PATH=/usr/bin  -DCMAKE_INSTALL_PREFIX=run ../ && \
  /usr/bin/cmake --build . --target extra && \
  ls ../ && \
  /usr/bin/cmake --build . && \
  /usr/bin/cmake --build . && \
  /usr/bin/cmake --build . --target install && \
  ls run/bin/ && \
  run/bin/sea -h && \
  /usr/bin/cmake --build . --target test-simple

# Install
RUN \
  sudo apt-get update && \
  apt-get install python2.7 python2.7-dev -y && \
  apt-get install --yes python-pip && \
  sudo pip install wllvm && \
  export LLVM_COMPILER=clang && \
  apt-get install --yes  gcc make libffi-dev pkg-config libz-dev libbz2-dev libsqlite3-dev libexpat1-dev libssl-dev libgdbm-dev tk-dev libgc-dev python-cffi liblzma-dev libncurses5-dev
RUN \
  sudo apt-get update && \
  sudo apt-get install python-software-properties software-properties-common -y -f   && \
  sudo add-apt-repository ppa:pypy/ppa -y  && \
  sudo apt-get update  && \
  apt-get install pypy -y  && \
  apt-get install python-pip python-dev build-essential -y  && \
  apt-get install --yes  git && \
  sudo apt-get install --yes mercurial && \
  hg clone http://bitbucket.org/pypy/pypy pypy && \
  cd /pypy/pypy/goal
  #git clone -b release-pypy2.7-v6.0.0 https://github.com/mesalock-linux/mesapy.git 
  pypy ../../rpython/bin/rpython --opt=jit targetpypystandalone.py
