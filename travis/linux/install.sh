#!/bin/sh -x

if [ "$TRAVIS_OS_NAME" = "linux" ]; then 
    sudo apt-get -qq -y install build-essential software-properties-common zlib1g-dev
    sudo add-apt-repository ppa:ubuntu-toolchain-r/test -y
    sudo apt-get -qq update -y
    sudo apt-get -qq install gcc-7 g++-7 subversion make cmake python libtool zlib1g zlib1g-dev -y
    sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-7 60 --slave /usr/bin/g++ g++ /usr/bin/g++-7
     sudo update-alternatives --config gcc
     sudo apt-get -qq -y install cppcheck
     sudo apt-get -y -qq install
     wget --no-check-certificate -q ${SDE_URL} -O sdetool.tar.bz2; tar -jxf sdetool.tar.bz2
fi
