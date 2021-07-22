#!/bin/bash

if [ -z $1 ]; then
	echo "Specify the absolute path of the toolchain"
	exit 0
fi

cmake -DTOOLCHAIN_BASE_PATH=$1 -DCMAKE_TOOLCHAIN_FILE=../sources/Aarch64Toolchain -DCMAKE_INSTALL_PREFIX=../install ../sources