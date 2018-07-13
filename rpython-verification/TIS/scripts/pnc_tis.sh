#!/bin/bash
set -x

# to generate the filesystem if needed:
# tis-mkfs -o tis/filesystems/pnc_map.c -local "modules/map/data/sunnyvale_loop/base_map_test.bin:modules/map/data/sunnyvale_loop/base_map_test.bin"
# superseeded by
# tis-mkfs -o tis/filesystems/pnc_map.c -local "modules/map/data/sunnyvale_loop/base_map_test.bin:modules/map/hdmap/test-data/base_map.bin"

FILES=(
    # tis/docker_internal/generated/protobuf/modules/routing/proto/routing.pb.cc
    modules/map/hdmap/adapter/opendrive_adapter.cc
    modules/common/util/file.cc
    modules/common/util/string_util.cc
    modules/map/hdmap/hdmap.cc
    modules/map/hdmap/hdmap_impl.cc
    #    modules/map/hdmap/hdmap_util.cc
    modules/map/pnc_map/pnc_map.cc
    tis/docker_internal/generated/protobuf/modules/common/proto/error_code.pb.cc
    tis/docker_internal/generated/protobuf/modules/common/proto/geometry.pb.cc
    tis/docker_internal/generated/protobuf/modules/common/proto/header.pb.cc
    tis/docker_internal/generated/protobuf/modules/map/proto/map.pb.cc
    tis/docker_internal/generated/protobuf/modules/map/proto/map_clear_area.pb.cc
    tis/docker_internal/generated/protobuf/modules/map/proto/map_crosswalk.pb.cc
    tis/docker_internal/generated/protobuf/modules/map/proto/map_geometry.pb.cc
    tis/docker_internal/generated/protobuf/modules/map/proto/map_id.pb.cc
    tis/docker_internal/generated/protobuf/modules/map/proto/map_junction.pb.cc
    tis/docker_internal/generated/protobuf/modules/map/proto/map_lane.pb.cc
    tis/docker_internal/generated/protobuf/modules/map/proto/map_overlap.pb.cc
    tis/docker_internal/generated/protobuf/modules/map/proto/map_signal.pb.cc
    tis/docker_internal/generated/protobuf/modules/map/proto/map_speed_bump.pb.cc
    tis/docker_internal/generated/protobuf/modules/map/proto/map_stop_sign.pb.cc
    tis/docker_internal/generated/protobuf/modules/map/proto/map_yield_sign.pb.cc
    tis/docker_internal/generated/protobuf/modules/map/proto/map_road.pb.cc
    tis/docker_internal/generated/protobuf/modules/routing/proto/routing.pb.cc
    tis/docker_internal/src/com_github_gflags_gflags/src/gflags.cc
    #tis/docker_internal/src/glog/src/logging.cc
    #tis/docker_internal/src/glog/src/utilities.cc
    tis/extern/error_code.ipp
    modules/map/pnc_map/pnc_map_tis_test.cc
)

OPT=(
    -fs-no-err tis/filesystems/pnc_map.c # filesystem used by the test
    -gui
    -slevel 1300000
    -val
    -val-interpreter-mode
    -val-malloc-plevel 13000000
    -val-slevel-merge-after-loop=-@all
)

./tis/protobuf.sh "${FILES[@]}" "${OPT[@]}" "$@"
