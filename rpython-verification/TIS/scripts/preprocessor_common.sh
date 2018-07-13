# Generic preprocessor options. Is expected to be sourced by other scripts.
PP_OPT=(
    -D _Atomic_word=int # workaround for opencv

    -D CPU_ONLY
    # Eigen configuration. Remove all fancy optimization.
    -D EIGEN_ALLOCA=malloc
    -D EIGEN_MAX_ALIGN_BYTES=0
    -D EIGEN_DONT_VECTORIZE
    -D EIGEN_MPL2_ONLY # found in compilation lines, don't know what this means.
    -D GTEST_USE_OWN_TR1_TUPLE=1 # tr1 tuple seem not the be compatible with our STL. To investigate
    -D HAVE_PTHREAD # protobuf
    -D USE_ESD_CAN=false

    -U _FORTIFY_SOURCE


    # Missing declarations
    -I /home/trustinsoft/git/apollo/tis/includes
    #-I /usr/include/x86_64-linux-gnu
    #-I /home/trustinsoft/git/apollo/tis/includes/glog
    -I /home/trustinsoft/git/apollo
    # Standard includes
    -I .
    -I /home/trustinsoft/git/apollo/modules/drivers/pandora/pandora_driver/src/Pandar40P
    -I local_integ/include/lidar_locator.h
    -I /home/trustinsoft/git/apollo/tis/docker_internal/local/apollo/local_integ/
    -I /home/trustinsoft/git/apollo/tis/docker_internal/local/include
    -I /home/trustinsoft/git/apollo/tis/docker_internal/local/include/cuda/include
    -I /home/trustinsoft/git/apollo/tis/docker_internal/local/include/pcl-1.7
    -I /home/trustinsoft/git/apollo/tis/docker_internal/local/include/node
    -I /home/trustinsoft/git/apollo/tis/docker_internal/local/ipopt/include/coin
    -I /home/trustinsoft/git/apollo/tis/docker_internal/include
    -I /home/trustinsoft/git/apollo/tis/docker_internal/include/vtk-5.8

    ## googletest # has to be before protobuf because of googlemock clash.
    ##-I /home/trustinsoft/git/apollo/tis/docker_internal/src/gtest/googletest
    ##-I /home/trustinsoft/git/apollo/tis/docker_internal/src/gtest/googletest/include

   # -I /home/trustinsoft/git/apollo/tis/docker_internal/src/com_google_protobuf/src
    -I /home/trustinsoft/git/apollo/tis/docker_internal/src/curlpp/include/curlpp
    -I /home/trustinsoft/git/apollo/tis/docker_internal/generated/protobuf
    -I /home/trustinsoft/git/apollo/tis/docker_internal/src/
    -I /home/trustinsoft/git/apollo/tis/docker_internal/src/civetweb/include
    -I /home/trustinsoft/git/apollo/tis/docker_internal/src/eigen
    -I /home/trustinsoft/git/apollo/tis/docker_internal/src/gtest/googlemock/include
    -I /home/trustinsoft/git/apollo/tis/docker_internal/src/opencv2/include
    -I /home/trustinsoft/git/apollo/tis/docker_internal/src/opencv2/modules/core/include
    -I /home/trustinsoft/git/apollo/tis/docker_internal/src/yaml_cpp/include
    -I /home/trustinsoft/git/apollo/tis/docker_internal/include/opencv2
    -I /home/trustinsoft/git/apollo/tis/docker_internal/src/ros/include
    -I /home/trustinsoft/git/apollo/tis/docker_internal/src/com_github_gflags_gflags/src
    # googletest
    # -I /home/trustinsoft/git/apollo/tis/docker_internal/src/gtest/googletest
    # -I /home/trustinsoft/git/apollo/tis/docker_internal/src/gtest/googletest/include

    # protobuf
    -I /home/trustinsoft/git/apollo/tis/docker_internal/src/com_google_protobuf/src
    #-I /tmp/usession-release-pypy2.7-v6.0.0-trustinsoft/testing_1
    #-I /home/trustinsoft/git/mesapy/rpython/translator/c
    -D HAVE_PTHREAD


)
