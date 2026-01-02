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
    amalg "to create the single header file"
)

__amalgamate() {
    local -a pugixml_files=(
        src/thirdparty/pugixml/pugiconfig.hpp
        src/thirdparty/pugixml/pugixml.hpp
        src/thirdparty/pugixml/pugixml.cpp

    )
    local -a zip_files=(
        src/thirdparty/zip/miniz.h
        src/thirdparty/zip/zip.h
        src/thirdparty/zip/zip.c

    )
    local -a duckx_files=(
        src/duckx.hpp
        src/duckx.cpp
    )

    local DUCKX_AMALG="duckx_amalg.hpp"

    # also create a new file
    [[ -f $DUCKX_AMALG ]] && rm $DUCKX_AMALG

    # add include guard
    echo "#ifndef DUCKX_AMALG_HPP" >> $DUCKX_AMALG
    echo "#define DUCKX_AMALG_HPP" >> $DUCKX_AMALG
    echo "" >> $DUCKX_AMALG

    # add pugixml
    cat "${pugixml_files[0]}" >> $DUCKX_AMALG
    # make pugixml act like header only library
    sed -i 's:// \(#define PUGIXML_HEADER_ONLY\):\1:' $DUCKX_AMALG
    echo "" >> $DUCKX_AMALG
    cat "${pugixml_files[1]}" >> $DUCKX_AMALG
    echo "" >> $DUCKX_AMALG
    cat "${pugixml_files[2]}" >> $DUCKX_AMALG
    echo "" >> $DUCKX_AMALG

    # add zip
    cat "${zip_files[0]}" >> $DUCKX_AMALG
    echo "" >> $DUCKX_AMALG
    cat "${zip_files[1]}" >> $DUCKX_AMALG
    echo "" >> $DUCKX_AMALG
    # make sure zip.c gets compiled properly for c++
    echo "#ifdef __cplusplus"
    echo 'extern "C" {'
    echo "#endif"
    cat "${zip_files[2]}" >> $DUCKX_AMALG
    echo "" >> $DUCKX_AMALG
    # make sure zip.c gets compiled properly for c++
    echo "#ifdef __cplusplus"
    echo "}"
    echo "#endif"

    # add duckx
    cat "${duckx_files[0]}" >> $DUCKX_AMALG
    sed -i 's/#include "thirdparty\/pugixml\/pugixml.hpp"//' $DUCKX_AMALG
    echo "" >> $DUCKX_AMALG
    # make act like header only lib
    echo "#ifdef DUCKX_IMPLEMENTATION" >> $DUCKX_AMALG
    cat "${duckx_files[1]}" >> $DUCKX_AMALG
    sed -i 's/#include "duckx.hpp"//' $DUCKX_AMALG
    sed -i 's/#include "thirdparty\/zip\/zip.h"//' $DUCKX_AMALG
    echo "#endif // DUCKX_IMPLEMENTATION" >> $DUCKX_AMALG
    # end include guard
    echo "" >> $DUCKX_AMALG
    echo "#endif // DUCKX_AMALG_HPP" >> $DUCKX_AMALG

    cat $DUCKX_AMALG
}

case "$1" in
    amalg)
        __amalgamate ;;
    build)
        __build true ;;
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
