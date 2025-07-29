cmake_minimum_required(VERSION 3.16)

project(glfw)

# Configure GLFW for static library build
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "Build the GLFW example programs")
set(GLFW_BUILD_TESTS OFF CACHE BOOL "Build the GLFW test programs")
set(GLFW_BUILD_DOCS OFF CACHE BOOL "Build the GLFW documentation")
set(GLFW_INSTALL OFF CACHE BOOL "Generate installation target")

# Define source files
file(GLOB SOURCES 
    "glfw/include/**.h"
    "glfw/src/*.c"
    "glfw/src/*.h"
)

# Remove platform-specific files that aren't needed
if(WIN32)
    list(FILTER SOURCES EXCLUDE REGEX ".*(cocoa|x11|wl|glx|posix|xkb|linux).*")
elseif(UNIX AND NOT APPLE)
    list(FILTER SOURCES EXCLUDE REGEX ".*(win32|cocoa|wgl|null).*")
endif()

# Create the library
add_library(glfw STATIC ${SOURCES})

# Add include directories
target_include_directories(glfw
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/glfw/include
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/glfw/src
)

# Define platform-specific options
if(WIN32)
    target_compile_definitions(glfw PRIVATE _GLFW_WIN32)
    target_link_libraries(glfw PRIVATE gdi32 user32 shell32)
elseif(UNIX AND NOT APPLE)
    target_compile_definitions(glfw PRIVATE _GLFW_X11 _GNU_SOURCE)
    find_package(X11 REQUIRED)
    target_link_libraries(glfw PRIVATE ${X11_LIBRARIES} dl pthread)
endif()

# Disable warnings for third-party code
target_compile_options(glfw PRIVATE 
    $<$<CXX_COMPILER_ID:MSVC>:/W0>
    $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-w>
)

# Configuration-specific settings
target_compile_definitions(glfw
    PRIVATE
        $<$<CONFIG:Debug>:DEBUG>
        $<$<CONFIG:Release>:NDEBUG>
)

set_target_properties(glfw PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/$<CONFIG>/glfw"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/$<CONFIG>/glfw"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/$<CONFIG>/glfw"
    FOLDER "examples/deps"
)
