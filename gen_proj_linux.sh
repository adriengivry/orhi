#!/bin/bash

pushd "$(dirname "$0")" > /dev/null
cmake -S . -B build \
    -DORHI_EXAMPLES_GFX_API=vulkan \
    -DORHI_COMPILE_VULKAN=ON \
    -DORHI_COMPILE_MOCK=ON \
    -DORHI_GENERATE_EXAMPLES=ON
popd > /dev/null
