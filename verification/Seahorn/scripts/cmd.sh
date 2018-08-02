#!/bin/bash

ls /pypy/rpython/translator/c/src/*.o |xargs -I % echo %.o > /pypy/rpython/translator/c/src/comm.namelist
cat /pypy/rpython/translator/c/src/comm.namelist | xargs -I % extract-bc % --output /pypy/rpython/translator/c/src/bc/%.bc
ls /pypy/rpython/translator/c/src/bc/*|xargs -I % ./sh.sh % > /pypy/rpython/translator/c/src/results
paste -d " " /pypy/rpython/translator/c/src/comm.namelist /pypy/rpython/translator/c/src/results > /pypy/rpython/translator/c/src/seahorn.results
