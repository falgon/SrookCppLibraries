#!/bin/sh -x

if [ "$TRAVIS_OS_NAME" = "osx" ]; then      
    brew update
    brew upgrade
    brew install gcc
    export CPU_NUM=`sysctl -n hw.logicalcpu_max`;
fi
