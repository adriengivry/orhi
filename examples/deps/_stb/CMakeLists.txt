cmake_minimum_required(VERSION 3.16)

project(stb)

# STB is a header-only library, just make it available for inclusion
add_library(stb INTERFACE)
target_include_directories(stb INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

set_target_properties(stb PROPERTIES
    FOLDER "examples/deps"
)
