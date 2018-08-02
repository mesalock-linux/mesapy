#!/bin/bash
set -x

# to generate the filesystem if needed:
# tis-mkfs -o tis/filesystems/pnc_map.c -local "modules/map/data/sunnyvale_loop/base_map_test.bin:modules/map/data/sunnyvale_loop/base_map_test.bin"
# superseeded by
# tis-mkfs -o tis/filesystems/pnc_map.c -local "modules/map/data/sunnyvale_loop/base_map_test.bin:modules/map/hdmap/test-data/base_map.bin"

FILES=(
    # tis/docker_internal/generated/protobuf/modules/routing/proto/routing.pb.cc
    #/home/trustinsoft/git/mesapy/rpython/translator/c/src/mem.c
    #/home/trustinsoft/git/mesapy/rpython/translator/c/src/thread.c
    #/home/trustinsoft/git/mesapy/rpython/translator/c/src/entrypoint.c
    /home/trustinsoft/git/mesapy/rpython/translator/c/src/ll_math.c
)

OPT=(
    #-fs-no-err tis/filesystems/pnc_map_filesystem.c # filesystem used by the test
    #-fs-no-err tis/filesystems/urandom_filesystem.c
    -gui
    -slevel 10
    -val
    -val-builtin 'cos:Frama_C_cos_precise,sin:Frama_C_sin_precise'
    #-val-interpreter-mode
    -val-malloc-plevel 10
    -val-slevel-merge-after-loop=-@all
    -no-val-warn-pointer-subtraction
)

./protobuf.sh "${FILES[@]}" "${OPT[@]}" "$@"
