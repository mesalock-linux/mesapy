#!/bin/bash

function build() {
    docker build -t mesapy-sgx  --build-arg UID=`id -u $USER` --build-arg GID=`id -g $USER` -f Dockerfile .
}

function run() {
    docker run --device /dev/isgx -u `id -u $USER` --rm -it -v`dirname $(pwd)`:/mesapy-sgx -w /mesapy-sgx/sgx mesapy-sgx
}

function usage() {
    echo "USAGE:"
    echo "    `basename $0` [OPTIONS]"
    echo ""
    echo "OPTIONS:"
    echo "    -h|-?                   Display this help message."
    echo "    build                   Build the docker image for building MesaPy for SGX"
    echo "    run                     Run the docker image"
}

function main() {
    while getopts ":h?" opt; do
        case ${opt} in
            h|?)
                usage
                exit 0
            ;;
            \?)
                echo "Unknown option: -$OPTARG" 1>&2
                exit 1
                ;;
        esac
    done

    shift $((OPTIND-1))
    subcommand=$1; shift

    case "$subcommand" in
        build)
            build
            ;;
        run)
            run
            ;;
        *)
            echo "Missing/unknown command ${subcommand}" 1>&2
            usage
            exit 1
            ;;
    esac
}

main "$@"
