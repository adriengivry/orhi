cmake_minimum_required(VERSION 3.16)

project(3-texture)

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
add_executable(3-texture ${SOURCES} ${SHADERS})

# Set C++ standard
set_target_properties(3-texture PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/$<CONFIG>/3-texture"
)

# Add include directories
target_include_directories(3-texture
    PRIVATE
        ${CMAKE_SOURCE_DIR}/deps/_glm/glm
        ${CMAKE_SOURCE_DIR}/deps/_glfw/glfw/include
        ${CMAKE_SOURCE_DIR}/deps/_stb/stb
        ${CMAKE_SOURCE_DIR}/../../include
)

# Link libraries
target_link_libraries(3-texture
    PRIVATE
        glfw
        stb
        orhi
)

# Configuration-specific settings
target_compile_definitions(3-texture
    PRIVATE
        $<$<CONFIG:Debug>:DEBUG>
        $<$<CONFIG:Release>:NDEBUG>
)

# Platform-specific options
if(WIN32)
    target_compile_options(3-texture
        PRIVATE
            $<$<CONFIG:Debug>:/Zi /Od /MDd>
            $<$<CONFIG:Release>:/O2 /MD>
    )
else()
    target_compile_options(3-texture
        PRIVATE
            $<$<CONFIG:Debug>:-g -O0>
            $<$<CONFIG:Release>:-O3>
    )
endif()

# Compile shaders
compile_shaders(3-texture)

# Copy assets if they exist
if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/assets)
    copy_assets(3-texture)
endif()
