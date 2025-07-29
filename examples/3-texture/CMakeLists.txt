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
    VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/bin/$<CONFIG>/3-texture"
    FOLDER "examples"
)

# Link libraries
target_link_libraries(3-texture
    PRIVATE
        glfw
        stb
        glm
        orhi
)

# Add Vulkan libraries if using Vulkan API
if(ORHI_EXAMPLES_GFX_API STREQUAL "vulkan")
    target_include_directories(3-texture PRIVATE ${VULKAN_SDK_PATH}/include)
    target_link_directories(3-texture PRIVATE ${VULKAN_LIB_DIR})
    target_link_libraries(3-texture PRIVATE ${VULKAN_LIB_NAME})
    
    # Add platform-specific libraries
    if(UNIX AND NOT APPLE)
        if(DEFINED X11_LIBS)
            target_link_libraries(3-texture PRIVATE ${X11_LIBS})
        endif()
        if(DEFINED WAYLAND_LIBS)
            target_link_libraries(3-texture PRIVATE ${WAYLAND_LIBS})
        endif()
    endif()
endif()

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
compile_shaders(3-texture "${SHADERS}")

# Copy assets if they exist
if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/assets)
    copy_assets(3-texture)
endif()
