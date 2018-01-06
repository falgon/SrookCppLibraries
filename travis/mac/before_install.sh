#!/bin/sh -x

if [ "$TRAVIS_OS_NAME" = "osx" ]; then      
    brew update
    brew upgrade
    brew install gcc
fi
