#!/bin/bash

version=${1:-gmake}

pushd "$(dirname "$0")" > /dev/null
premake5 "$version" --compile-vulkan --compile-mock --gfxapi=vulkan
popd > /dev/null
