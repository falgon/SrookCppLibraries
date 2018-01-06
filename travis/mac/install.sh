#!/bin/sh -x

if [ "$TRAVIS_OS_NAME" = "osx" ]; then      
    brew install gcc
    brew install clang
    brew install cppcheck
fi
