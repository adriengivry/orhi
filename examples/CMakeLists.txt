cmake_minimum_required(VERSION 3.16)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Get Vulkan SDK path for shader compilation and linking
if(DEFINED ENV{VULKAN_SDK})
    set(VULKAN_SDK_PATH $ENV{VULKAN_SDK})
    message(STATUS "Found Vulkan SDK at: ${VULKAN_SDK_PATH}")

    # Set up Vulkan for all examples
    if(ORHI_COMPILE_VULKAN)
        # Make Vulkan include directory available to all examples
        include_directories(${VULKAN_SDK_PATH}/include)
        
        # Set up platform-specific Vulkan libraries
        if(WIN32)
            set(VULKAN_LIB_DIR ${VULKAN_SDK_PATH}/Lib)
            set(VULKAN_LIB_NAME vulkan-1)
        else()
            set(VULKAN_LIB_DIR ${VULKAN_SDK_PATH}/lib)
            set(VULKAN_LIB_NAME vulkan)
        endif()
        
        # Add X11 libraries for Linux if needed
        if(UNIX AND NOT APPLE)
            find_package(X11 REQUIRED)
            if(ORHI_WINDOW_SYSTEM STREQUAL "xlib")
                set(X11_LIBS ${X11_LIBRARIES})
            elseif(ORHI_WINDOW_SYSTEM STREQUAL "xcb")
                set(X11_LIBS ${X11_LIBRARIES} ${X11_xcb_LIB} X11-xcb)
            elseif(ORHI_WINDOW_SYSTEM STREQUAL "wayland")
                find_package(Wayland REQUIRED)
                set(WAYLAND_LIBS ${WAYLAND_LIBRARIES})
            endif()
        endif()
    endif()
else()
    message(WARNING "VULKAN_SDK environment variable not set. Shader compilation may fail.")
    set(VULKAN_SDK_PATH "")
endif()

# Function to compile shaders for a project
function(compile_shaders TARGET_NAME SHADER_SOURCES)
    # Create output directory
    set(SHADER_OUTPUT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/assets/shaders")
    file(MAKE_DIRECTORY ${SHADER_OUTPUT_DIR})
    
    # Set source file properties for shader files
    foreach(SHADER ${SHADER_SOURCES})
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
                VERBATIM
            )
        else()
            add_custom_command(
                OUTPUT ${SHADER_OUT}
                COMMAND ${VULKAN_SDK_PATH}/bin/glslangValidator -V ${SHADER} -o ${SHADER_OUT}
                DEPENDS ${SHADER}
                COMMENT "Compiling ${SHADER_EXT} shader: ${SHADER_NAME}"
                VERBATIM
            )
        endif()
        
        list(APPEND SHADER_OUTPUTS ${SHADER_OUT})
        # Add shader output to target sources
        target_sources(${TARGET_NAME} PRIVATE ${SHADER_OUT})
    endforeach()
    
    # Set a source group for shader files to organize them in IDEs
    source_group("Shader Files" FILES ${SHADER_SOURCES})
    source_group("Compiled Shaders" FILES ${SHADER_OUTPUTS})
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
