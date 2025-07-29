cmake_minimum_required(VERSION 3.16)

project(glm)

# GLM is a header-only library, just make it available for inclusion
add_library(glm INTERFACE)
target_include_directories(glm INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/glm)

set_target_properties(glm PROPERTIES
    FOLDER "examples/deps"
)
