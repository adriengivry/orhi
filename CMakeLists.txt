cmake_minimum_required(VERSION 3.16)
project(orhi)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(ORHI_COMPILE_VULKAN "Compile Vulkan backend" OFF)
option(ORHI_COMPILE_MOCK "Compile Mock backend" OFF)

if (ORHI_COMPILE_VULKAN)
    add_compile_definitions(ORHI_COMPILE_VULKAN)
    
    # Find Vulkan SDK
    if(DEFINED ENV{VULKAN_SDK})
        set(VULKAN_SDK_PATH $ENV{VULKAN_SDK})
        message(STATUS "Found Vulkan SDK at: ${VULKAN_SDK_PATH}")
    else()
        message(FATAL_ERROR "VULKAN_SDK environment variable not set. Please install Vulkan SDK and set VULKAN_SDK environment variable.")
    endif()
endif()

if (ORHI_COMPILE_MOCK)
    add_compile_definitions(ORHI_COMPILE_MOCK)
endif()

file(GLOB_RECURSE SOURCES "src/*.cpp" "src/*.c")
file(GLOB_RECURSE HEADERS "src/*.h" "include/*.h")
add_library(orhi ${SOURCES} ${HEADERS})

# Add include directory
target_include_directories(orhi
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include

    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# Add Vulkan include directories if enabled
if (ORHI_COMPILE_VULKAN)
    target_include_directories(orhi
        PRIVATE
            ${VULKAN_SDK_PATH}/include
    )
endif()
