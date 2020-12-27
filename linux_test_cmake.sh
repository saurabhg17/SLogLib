#!/bin/bash

mkdir debug_shared
cd debug_shared
cmake -DSLOGLIB_BUILD_SHARED_LIBS=ON -DCMAKE_BUILD_TYPE=Debug ../../sources
make -j 10
cd ..

mkdir release_shared
cd release_shared
cmake -DSLOGLIB_BUILD_SHARED_LIBS=ON -DCMAKE_BUILD_TYPE=Release ../../sources
make -j 10
cd ..

mkdir releasewithdebinfo_shared
cd releasewithdebinfo_shared
cmake -DSLOGLIB_BUILD_SHARED_LIBS=ON -DCMAKE_BUILD_TYPE=RelWithDebInfo ../../sources
make -j 10
cd ..

mkdir minsizerel_shared
cd minsizerel_shared
cmake -DSLOGLIB_BUILD_SHARED_LIBS=ON -DCMAKE_BUILD_TYPE=MinSizeRel ../../sources
make -j 10
cd ..




mkdir debug_static
cd debug_static
cmake -DSLOGLIB_BUILD_SHARED_LIBS=OFF -DCMAKE_BUILD_TYPE=Debug ../../sources
make -j 10
cd ..

mkdir release_static
cd release_static
cmake -DSLOGLIB_BUILD_SHARED_LIBS=OFF -DCMAKE_BUILD_TYPE=Release ../../sources
make -j 10
cd ..

mkdir releasewithdebinfo_static
cd releasewithdebinfo_static
cmake -DSLOGLIB_BUILD_SHARED_LIBS=OFF -DCMAKE_BUILD_TYPE=RelWithDebInfo ../../sources
make -j 10
cd ..

mkdir minsizerel_static
cd minsizerel_static
cmake -DSLOGLIB_BUILD_SHARED_LIBS=OFF -DCMAKE_BUILD_TYPE=MinSizeRel ../../sources
make -j 10
cd ..
