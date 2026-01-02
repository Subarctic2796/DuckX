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
    build        "to build the project"
    test         "to test the project"
    amalg        "to create the single header file"
    'test-amalg' "to test that the amalgamation compiles properly"
)


__amalgamate_add_pugixml() {
    local -A pugixml_files=(
        config src/thirdparty/pugixml/pugiconfig.hpp
        hpp    src/thirdparty/pugixml/pugixml.hpp
        cpp    src/thirdparty/pugixml/pugixml.cpp
    )
    local DUCKX_AMALG="duckx_amalg.hpp"

    # pugiconfig.hpp
    cat "${pugixml_files[config]}" >> $DUCKX_AMALG
    # make pugixml act like header only library
    sed -i 's:// \(#define PUGIXML_HEADER_ONLY\):\1:' $DUCKX_AMALG
    echo "" >> $DUCKX_AMALG

    # pugixml.hpp
    # replace '#include PUGIXML_SOURCE' with pugixml.cpp
    # this is the size of the license on other stuff needed
    local last26="$(tail -n 26 ${pugixml_files[hpp]})"
    local nlines=$(wc -l ${pugixml_files[hpp]})
    nlines=${nlines%[[:space:]]*}
    head -n $(( nlines - 27 )) ${pugixml_files[hpp]} >> $DUCKX_AMALG

    # pugixml.cpp
    cat "${pugixml_files[cpp]}" >> $DUCKX_AMALG
    echo "$last26" >> $DUCKX_AMALG

    # remove '#include "pugiconfig.hpp"'
    sed -i 's/#include "pugiconfig.hpp"//' $DUCKX_AMALG
    # remove '#include "pugixml.hpp"'
    sed -i 's/#include "pugixml.hpp"//' $DUCKX_AMALG

    echo "" >> $DUCKX_AMALG
}

__amalgamate_add_zip() {
    local -A zip_files=(
        miniz src/thirdparty/zip/miniz.h
        h     src/thirdparty/zip/zip.h
        c     src/thirdparty/zip/zip.c
    )
    local DUCKX_AMALG="duckx_amalg.hpp"

    cat "${zip_files[miniz]}" >> $DUCKX_AMALG
    echo "" >> $DUCKX_AMALG
    cat "${zip_files[h]}" >> $DUCKX_AMALG
    echo "" >> $DUCKX_AMALG
    # make sure zip.c gets compiled properly for c++
    echo "#ifdef __cplusplus
extern \"C\" {
#endif" >> $DUCKX_AMALG
    cat "${zip_files[c]}" >> $DUCKX_AMALG
    echo "" >> $DUCKX_AMALG
    # make sure zip.c gets compiled properly for c++
    echo "#ifdef __cplusplus
}
#endif" >> $DUCKX_AMALG

    # remove '#include "miniz.h"'
    sed -i 's/#include "miniz.h"//' $DUCKX_AMALG
    # remove '#include "zip.h"'
    sed -i 's/#include "zip.h"//' $DUCKX_AMALG
}

__amalgamate_add_duckx() {
    local -A duckx_files=(
        hpp src/duckx.hpp
        cpp src/duckx.cpp
    )

    local DUCKX_AMALG="duckx_amalg.hpp"

    cat "${duckx_files[hpp]}" >> $DUCKX_AMALG
    sed -i 's/#include "thirdparty\/pugixml\/pugixml.hpp"//' $DUCKX_AMALG
    echo "" >> $DUCKX_AMALG
    # make act like header only lib
    echo "#ifdef DUCKX_IMPLEMENTATION" >> $DUCKX_AMALG
    cat "${duckx_files[cpp]}" >> $DUCKX_AMALG
    sed -i 's/#include "duckx.hpp"//' $DUCKX_AMALG
    sed -i 's/#include "thirdparty\/zip\/zip.h"//' $DUCKX_AMALG
    echo "#endif // DUCKX_IMPLEMENTATION" >> $DUCKX_AMALG
}

__amalgamate() {
    local DUCKX_AMALG="duckx_amalg.hpp"

    # always create a new file
    [[ -f $DUCKX_AMALG ]] && rm $DUCKX_AMALG

    # add include guard
    echo "#ifndef DUCKX_AMALG_HPP
#define DUCKX_AMALG_HPP
" >> $DUCKX_AMALG

    __amalgamate_add_pugixml
    __amalgamate_add_zip
    __amalgamate_add_duckx

    # end include guard
    echo "
#endif // DUCKX_AMALG_HPP" >> $DUCKX_AMALG
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
    'test-amalg')
        __amalgamate
        clang++ -Wall -Wextra -xc++ -c duckx_amalg.hpp 2> /dev/null
        test_code=$?
        if (( test_code != 0 )); then
            echo "compiling failed"
            clang++ -Wall -Wextra -xc++ -c duckx_amalg.hpp
        fi
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
