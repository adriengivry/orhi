cmake_minimum_required(VERSION 3.16)
project(orhi)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Define options
option(ORHI_COMPILE_VULKAN "Compile Vulkan backend" OFF)
option(ORHI_COMPILE_MOCK "Compile Mock backend" OFF)
option(ORHI_GENERATE_EXAMPLES "Generate examples" OFF)

# Window system selection
set(ORHI_WINDOW_SYSTEM "xlib" CACHE STRING "Select window management system")
set_property(CACHE ORHI_WINDOW_SYSTEM PROPERTY STRINGS "xlib" "xcb" "wayland" "none")

# Window system configuration
if (ORHI_WINDOW_SYSTEM STREQUAL "none")
    message(STATUS "Headless mode selected")
    add_compile_definitions(ORHI_HEADLESS)
endif()

# Platform-specific window system handling
if (CMAKE_SYSTEM_NAME STREQUAL "Linux")
    if (ORHI_WINDOW_SYSTEM STREQUAL "xlib")
        message(STATUS "Xlib window system selected")
        add_compile_definitions(ORHI_USE_XLIB)
        find_package(X11 REQUIRED)
    elseif (ORHI_WINDOW_SYSTEM STREQUAL "xcb")
        message(STATUS "XCB window system selected")
        add_compile_definitions(ORHI_USE_XCB)
        find_package(X11 REQUIRED)
    elseif (ORHI_WINDOW_SYSTEM STREQUAL "wayland")
        message(STATUS "Wayland window system selected")
        add_compile_definitions(ORHI_USE_WAYLAND)
        find_package(Wayland REQUIRED)
    endif()
endif()

# Backend configuration
if (ORHI_COMPILE_VULKAN)
    message(STATUS "Vulkan backend selected for compilation")
    add_compile_definitions(ORHI_COMPILE_VULKAN)
    
    # Check for Vulkan SDK
    if(DEFINED ENV{VULKAN_SDK})
        set(VULKAN_SDK_PATH $ENV{VULKAN_SDK})
        message(STATUS "Found Vulkan SDK at: ${VULKAN_SDK_PATH}")
    else()
        message(FATAL_ERROR "VULKAN_SDK environment variable not set. Please install Vulkan SDK and set VULKAN_SDK environment variable.")
    endif()
endif()

if (ORHI_COMPILE_MOCK)
    message(STATUS "Mock backend selected for compilation")
    add_compile_definitions(ORHI_COMPILE_MOCK)
endif()

# Set output directories to match premake5 structure
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/$<CONFIG>/orhi)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/$<CONFIG>/orhi)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/$<CONFIG>/orhi)

# Create the library
file(GLOB_RECURSE PRIVATE_SRC "src/*.cpp" "src/*.c" "src/*.h")
file(GLOB_RECURSE PUBLIC_SRC "include/*.h")
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/src PREFIX "src" FILES ${PRIVATE_SRC})
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/include PREFIX "include" FILES ${PUBLIC_SRC})
add_library(orhi STATIC ${PRIVATE_SRC} ${PUBLIC_SRC})

# Add include directory
target_include_directories(orhi
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# Add Vulkan include directories and libraries if enabled
if (ORHI_COMPILE_VULKAN)
    target_include_directories(orhi
        PRIVATE
            ${VULKAN_SDK_PATH}/include
    )
    
    # Link against Vulkan library
    if(WIN32)
        target_link_directories(orhi PRIVATE ${VULKAN_SDK_PATH}/Lib)
        target_link_libraries(orhi PRIVATE vulkan-1)
    else()
        target_link_directories(orhi PRIVATE ${VULKAN_SDK_PATH}/lib)
        target_link_libraries(orhi PRIVATE vulkan)
        
        # Add X11 libraries for Linux
        if(UNIX AND NOT APPLE)
            find_package(X11 REQUIRED)
            if(ORHI_WINDOW_SYSTEM STREQUAL "xlib")
                target_link_libraries(orhi PRIVATE ${X11_LIBRARIES})
            elseif(ORHI_WINDOW_SYSTEM STREQUAL "xcb")
                target_link_libraries(orhi PRIVATE ${X11_LIBRARIES} ${X11_xcb_LIB} X11-xcb)
            elseif(ORHI_WINDOW_SYSTEM STREQUAL "wayland")
                find_package(Wayland REQUIRED)
                target_link_libraries(orhi PRIVATE ${WAYLAND_LIBRARIES})
            endif()
        endif()
    endif()
endif()

# Configuration-specific settings
target_compile_definitions(orhi
    PRIVATE
        $<$<CONFIG:Debug>:DEBUG>
        $<$<CONFIG:Release>:NDEBUG>
)

# Debug configuration
set_target_properties(orhi PROPERTIES
    DEBUG_POSTFIX ""
)

# Include examples if the option is enabled
if(ORHI_GENERATE_EXAMPLES)
    message(STATUS "Generating OpenRHI examples...")
    add_subdirectory(examples)
    set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT 1-triangle)
endif()
