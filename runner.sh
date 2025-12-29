#!/usr/bin/env bash

__build() {
    if [[ ! -d build ]]; then
        mkdir build
        cd build
        cmake ..
        cd ..
    fi
    cd build
    cmake --build .
    if [[ $1 == "true" ]]; then
        cd ..
    fi
}

case "$1" in
    build)
        __build true
        ;;
    test)
        __build
        cd test

        ./unit_tests
        echo
        ./iterator_tests
        ;;
    *)
        echo "unknown command \"$1\""
        exit 1
        ;;
esac
