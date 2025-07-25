cmake_minimum_required(VERSION 3.16)

project(1-triangle)

# Find source files
file(GLOB_RECURSE SOURCES "*.cpp" "*.h")

# Add shader files to the project
file(GLOB_RECURSE SHADERS
    "*.vert"
    "*.frag"
    "*.comp"
    "*.geom"
    "*.tesc"
    "*.tese"
)

# Create the executable
add_executable(1-triangle ${SOURCES} ${SHADERS})

# Set C++ standard
set_target_properties(1-triangle PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/$<CONFIG>/1-triangle"
)

# Add include directories
target_include_directories(1-triangle
    PRIVATE
        ${CMAKE_SOURCE_DIR}/deps/_glm/glm
        ${CMAKE_SOURCE_DIR}/deps/_glfw/glfw/include
        ${CMAKE_SOURCE_DIR}/../../include
)

# Link libraries
target_link_libraries(1-triangle
    PRIVATE
        glfw
        orhi
)

# Configuration-specific settings
target_compile_definitions(1-triangle
    PRIVATE
        $<$<CONFIG:Debug>:DEBUG>
        $<$<CONFIG:Release>:NDEBUG>
)

# Platform-specific options
if(WIN32)
    target_compile_options(1-triangle
        PRIVATE
            $<$<CONFIG:Debug>:/Zi /Od /MDd>
            $<$<CONFIG:Release>:/O2 /MD>
    )
else()
    target_compile_options(1-triangle
        PRIVATE
            $<$<CONFIG:Debug>:-g -O0>
            $<$<CONFIG:Release>:-O3>
    )
endif()

# Compile shaders
compile_shaders(1-triangle)

# Copy assets if they exist
if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/assets)
    copy_assets(1-triangle)
endif()
