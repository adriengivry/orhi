set(GLFW_BUILD_INSTALL OFF CACHE BOOL "GLFW lib only")
set(GLFW_BUILD_TESTS OFF CACHE BOOL "GLFW lib only")
set(GLFW_BUILD_DOCS OFF CACHE BOOL "GLFW lib only")
set(GLFW_INSTALL OFF CACHE BOOL "GLFW lib only")

add_subdirectory(glfw)

set_target_properties(
    glfw
    update_mappings
    PROPERTIES FOLDER "examples/deps/glfw"
)
