:q#!/bin/bash

OPTS=(
    # other opts
    # -address-alignment 8 # because protobuf. See UTF8GenericScanFastAscii
    -address-alignment 16 # because eigen. See plain_array() in DenseStorage.h
    # -slevel 1000
    -unsafe-arrays # because protobuf :(
    -val-clone-on-recursive-calls
    # -val-interpreter-mode # do not set it by default
    # -val-malloc-plevel 200 # protobuf init
    -val-malloc-plevel 400 # protobuf init
    -val-ptr-total-comparison
    -info-csv-functions pnc_functions.csv
    -info-csv-statements pnc_statements.csv
     #-metrics    
)

BUILTINS=(
    ceilf:Frama_C_ceilf
    atan2:Frama_C_atan2
    fmin:Frama_C_fmin
    fmax:Frama_C_fmax
)

RUNTIMES=(
    ##/home/trustinsoft/git/apollo/tis/docker_internal/src/gtest/googletest/src/gtest-all.cc

    # # google glog. Can't include all files in one file, since some of their
    # # headers (eg. googletest.h) should not be included multple times. Duh.
    # # tis/docker_internal/src/glog/src/vlog_is_on.cc
    # tis/docker_internal/src/glog/src/raw_logging.cc
    # # tis/docker_internal/src/glog/src/mock-log_test.cc
    # # tis/docker_internal/src/glog/src/stacktrace_unittest.cc
    # # tis/docker_internal/src/glog/src/logging_unittest.cc
    # # tis/docker_internal/src/glog/src/signalhandler.cc
    # # tis/docker_internal/src/glog/src/utilities_unittest.cc
    # # tis/docker_internal/src/glog/src/signalhandler_unittest.cc
    # # tis/docker_internal/src/glog/src/symbolize.cc
    # # tis/docker_internal/src/glog/src/stl_logging_unittest.cc
    # # tis/docker_internal/src/glog/src/symbolize_unittest.cc
    # # tis/docker_internal/src/glog/src/demangle_unittest.cc
    # tis/docker_internal/src/glog/src/logging.cc
    # tis/docker_internal/src/glog/src/utilities.cc
    # # tis/docker_internal/src/glog/src/demangle.cc

    #/home/trustinsoft/git/apollo/tis/runtimes/libcxx-runtime.cpp
    #/home/trustinsoft/git/apollo/tis/runtimes/protobuf-runtime.cpp
)

./analyzer.sh "${OPTS[@]}" ${BUILTINS[@]/#/-val-builtin } "${RUNTIMES[@]}" "$@"
