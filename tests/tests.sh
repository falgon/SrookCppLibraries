#!/bin/bash
SDE_PATH=/sde-external-8.56.0-2020-07-05-lin/sde64
BOOST_PGOPT_LIB="-L/usr/local/lib -lboost_program_options -lz -pthread"

P=$(nproc)

make -j$P GXX=g++
make run GXX=g++
make clean
make \
    -f Makefile.zlib \
    -j$P GXX=g++ LIBS="$BOOST_PGOPT_LIB" run clean
chmod +x ./cstring/sde_script.sh
./cstring/sde_script.sh 1
./cstring/sde_script.sh 0
make -f ./cstring/Makefile -j$P GXX=g++ SDE=$SDE_PATH 
make -f ./cstring/Makefile GXX=g++ SDE=$SDE_PATH run clean
