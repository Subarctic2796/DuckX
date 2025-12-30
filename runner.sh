#!/usr/bin/env bash

__build() {
    if [[ ! -d build ]]; then
        mkdir build && cd build
        cmake ..
        cd ..
    fi
    [[ "${PWD##*/}" != "build" ]] && cd build || true
    cmake --build .
    if [[ $1 == "true" ]]; then
        cd ..
    fi
}

declare -A subcommands=(
    build "to build the project"
    test  "to test the project"
)

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
        echo "options:"
        for i in "${!subcommands[@]}"; do
            value=${subcommands[$i]}
            echo "    $i    $value"
        done
        exit 1
        ;;
esac
