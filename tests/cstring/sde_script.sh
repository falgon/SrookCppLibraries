#!/bin/sh -x

check_avx512 () {
    if [ $1 -gt 0 ]; then
        FLAG="-DSROOK_CONFIG_ENABLE_AVX512_MEMCPY -mavx512f"
    else
        FLAG=""
    fi
    g++ ${FLAG} -I../ -isystem ../include -S -std=c++14 ./cstring/memcpy/avx512_test.cpp
    I=`cat avx512_test.s | grep vmovdqu | wc -l`

    rm avx512_test.s
    if [ $I -gt 0 ]; then
        case "$1" in
            0) return 1;;
            *) return 0;;
        esac
    else
        case "$1" in
            0) return 0;;
            *) return 1;;
        esac
    fi
}

check_avx512 $@
