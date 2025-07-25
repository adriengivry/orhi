cmake_minimum_required(VERSION 3.16)

message("Configuring orhi-examples...")

# Set output directories to match the previous premake structure
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/$<CONFIG>)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/$<CONFIG>)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/$<CONFIG>)

# Options for backend selection
if(NOT DEFINED ORHI_EXAMPLES_GFX_API)
    set(ORHI_EXAMPLES_GFX_API "vulkan" CACHE STRING "Define the graphics API to use (e.g., vulkan, mock)")
    set_property(CACHE ORHI_EXAMPLES_GFX_API PROPERTY STRINGS "vulkan" "mock")
endif()

# Configure based on selected API
if(ORHI_EXAMPLES_GFX_API STREQUAL "vulkan")
    message("+ Using Vulkan as the graphics API for examples")
    add_compile_definitions(ORHI_SELECT_VULKAN)
elseif(ORHI_EXAMPLES_GFX_API STREQUAL "mock")
    message("+ Using Mock as the graphics API for examples")
    add_compile_definitions(ORHI_SELECT_MOCK)
endif()

# Get Vulkan SDK path for shader compilation
if(DEFINED ENV{VULKAN_SDK})
    set(VULKAN_SDK_PATH $ENV{VULKAN_SDK})
    message("+ Found Vulkan SDK at: ${VULKAN_SDK_PATH}")
else()
    message(WARNING "VULKAN_SDK environment variable not set. Shader compilation may fail.")
    set(VULKAN_SDK_PATH "")
endif()

# Function to compile shaders for a project
function(compile_shaders TARGET_NAME)
    # Get all shader files from the project directory
    file(GLOB_RECURSE SHADER_FILES 
        "${CMAKE_CURRENT_SOURCE_DIR}/*.vert"
        "${CMAKE_CURRENT_SOURCE_DIR}/*.frag"
        "${CMAKE_CURRENT_SOURCE_DIR}/*.comp"
        "${CMAKE_CURRENT_SOURCE_DIR}/*.geom"
        "${CMAKE_CURRENT_SOURCE_DIR}/*.tesc"
        "${CMAKE_CURRENT_SOURCE_DIR}/*.tese"
    )
    
    # Create output directory
    set(SHADER_OUTPUT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/assets/shaders")
    file(MAKE_DIRECTORY ${SHADER_OUTPUT_DIR})
    
    # Add custom commands for each shader
    foreach(SHADER ${SHADER_FILES})
        get_filename_component(SHADER_NAME ${SHADER} NAME)
        get_filename_component(SHADER_EXT ${SHADER} EXT)
        string(REPLACE "." "" SHADER_EXT ${SHADER_EXT})
        
        set(SHADER_OUT "${SHADER_OUTPUT_DIR}/${SHADER_NAME}.spv")
        
        if(WIN32)
            add_custom_command(
                OUTPUT ${SHADER_OUT}
                COMMAND ${VULKAN_SDK_PATH}/bin/glslangValidator.exe -V ${SHADER} -o ${SHADER_OUT}
                DEPENDS ${SHADER}
                COMMENT "Compiling ${SHADER_EXT} shader: ${SHADER_NAME}"
            )
        else()
            add_custom_command(
                OUTPUT ${SHADER_OUT}
                COMMAND ${VULKAN_SDK_PATH}/bin/glslangValidator -V ${SHADER} -o ${SHADER_OUT}
                DEPENDS ${SHADER}
                COMMENT "Compiling ${SHADER_EXT} shader: ${SHADER_NAME}"
            )
        endif()
        
        list(APPEND SHADER_OUTPUTS ${SHADER_OUT})
    endforeach()
    
    # Create a custom target for the shaders
    if(SHADER_OUTPUTS)
        add_custom_target(
            ${TARGET_NAME}_shaders
            DEPENDS ${SHADER_OUTPUTS}
        )
        
        # Make the main target depend on the shaders
        add_dependencies(${TARGET_NAME} ${TARGET_NAME}_shaders)
    endif()
endfunction()

# Function to copy assets
function(copy_assets TARGET_NAME)
    add_custom_command(
        TARGET ${TARGET_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_CURRENT_SOURCE_DIR}/assets
            $<TARGET_FILE_DIR:${TARGET_NAME}>/assets
        COMMENT "Copying assets for ${TARGET_NAME}"
    )
endfunction()

# First, add the dependencies
add_subdirectory(deps/_glm)
add_subdirectory(deps/_glfw)
add_subdirectory(deps/_stb)

# Now add the example projects
add_subdirectory(1-triangle)
add_subdirectory(2-cube)
add_subdirectory(3-texture)
add_subdirectory(4-depth)
add_subdirectory(5-mipmaps)
add_subdirectory(6-msaa)
add_subdirectory(7-particles)
add_subdirectory(8-push-constants)
