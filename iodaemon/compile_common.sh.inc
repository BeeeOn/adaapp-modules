# Helper script for build
# TN, 2015

mkdir -p ${BUILD_DIR}
cd ${BUILD_DIR}
cmake ${CMAKE_ARGS} -DCMAKE_INSTALL_PREFIX=../${INSTALL_DIR} ..

make -j`nproc`
