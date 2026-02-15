#!/bin/bash

pushd "$(dirname "$0")" > /dev/null
cmake -S . -B build -G Xcode \
    -DORHI_DEFAULT_GFX_API=vulkan \
    -DORHI_COMPILE_VULKAN=ON \
    -DORHI_COMPILE_MOCK=ON \
    -DORHI_GENERATE_EXAMPLES=ON \
    -DCMAKE_C_COMPILER=/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/clang \
    -DCMAKE_CXX_COMPILER=/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/clang++ \
    -DCMAKE_OBJC_COMPILER=/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/clang++
popd > /dev/null
