@echo off

pushd "%~dp0"
cmake -S . -B build^
    -DORHI_COMPILE_VULKAN=ON^
    -DORHI_COMPILE_MOCK=ON^
    -DORHI_GENERATE_EXAMPLES=ON
popd
