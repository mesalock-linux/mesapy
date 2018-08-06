#!/bin/bash
/usr/bin/seapp -o $1.pp.bc --strip-extern=false --promote-assumptions=false --kill-vaarg=true $1
/usr/bin/seapp -o $0.pp1.bc --abc=global --abc-dsa-node=0 --abc-alloc-site=0 $1.pp.bc
/usr/bin/seapp -o $1.pp1.bc2.bc --horn-mixed-sem --ms-reduce-main $1.pp1.bc
/usr/bin/seaopt -f -funit-at-a-time -o $1.pp1.bc3.bc  --enable-indvar=false --enable-loop-idiom=false --enable-nondet-init=false --unroll-threshold=150 --disable-loop-vectorization=true --disable-slp-vectorization=true --vectorize-slp-aggressive=false $1.pp1.bc2.bc
/usr/bin/seahorn --keep-shadows=true --horn-solve -horn-inter-proc -horn-sem-lvl=mem --horn-step=large -horn-cex-pass -log=cex -horn-cex=/tmp/usession-default-2/testing_1/bc/$1.ll $1.pp1.bc3.bc 
