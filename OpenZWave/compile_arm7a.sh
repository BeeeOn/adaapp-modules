#!/bin/bash

# Crosscompilation for ARM

# Source toolchain for cross compilation
. /usr/local/beeeon-i686_v2/environment-setup-armv7a-vfp-neon-oe-linux-gnueabi


BUILD_DIR="build_arm7a"
mkdir -p ${BUILD_DIR}
cd ${BUILD_DIR}

export BUILD_DIR=build_armv7a
export CMAKE_ARGS="-DCMAKE_TOOLCHAIN_FILE=$OECORE_NATIVE_SYSROOT/usr/share/cmake/OEToolchainConfig.cmake"

cmake ${CMAKE_ARGS}  -DCMAKE_INSTALL_PREFIX=../${BUILD_DIR} ..

make -j 6
