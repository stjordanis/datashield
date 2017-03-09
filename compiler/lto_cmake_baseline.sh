#!/bin/sh

# this script will make a build directory and attempt to build clang/llvm with datashield

#rm -r build
#mkdir build
#cd build
cmake -G "Ninja" -DCMAKE_BUILD_TYPE=Release \
  -DCMAKE_C_COMPILER=clang \
  -DCMAKE_CXX_COMPILER=clang++ \
  -DLLVM_ENABLE_ASSERTIONS=ON \
  -DLLVM_BUILD_TESTS=OFF \
  -DLLVM_BUILD_EXAMPLES=OFF \
  -DLLVM_INCLUDE_TESTS=OFF\
  -DLLVM_INCLUDE_EXAMPLES=OFF \
  -DLLVM_TARGETS_TO_BUILD="X86" \
  -DBUILD_SHARED_LIBS=ON \
  -DLLVM_BINUTILS_INCDIR=/usr/include \
  -DCMAKE_INSTALL_PREFIX=$HOME/research/datashield/ds_sysroot_baseline \
  ../llvm
ninja
