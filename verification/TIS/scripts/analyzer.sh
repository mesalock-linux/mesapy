#!/bin/bash

set -x

source "$(dirname $BASH_SOURCE)/preprocessor_common.sh"

# tis-analyzer specific options
OPT=(
    -64
    -no-cxx-annot
    -no-cxx-precompile
    -no-cxx-runtime
    -fclang-cpp-extra-args="-mno-sse" # disable sse instructions
    -no-val-print
    -no-val-show-initial-state
    #    -no-val-show-progress
    #-metrics
)

SYSTEM_MODELISATION=(
    #gcc_builtins.c
    math.c # should not be here but in the libc runtime
    stdio.c
    stdlib.c
    syscall.c
    threads.c
    time.c
    unistd.c
)

tis-analyzer  "${OPT[@]}" "${PP_OPT[@]}" "${SYSTEM_MODELISATION[@]/#//home/trustinsoft/git/apollo/tis/system_modelisation/}" "$@" -D IEEE_8087 -D RPY_ASSERT -D PYPY_X86_CHECK_SSE2
