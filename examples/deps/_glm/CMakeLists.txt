set(GLM_BUILD_TESTS OFF CACHE BOOL "GLM lib only")
set(GLM_ENABLE_CXX_20 OFF CACHE BOOL "GLM lib only")

add_subdirectory(glm)

set_target_properties(
    glm
    PROPERTIES FOLDER "examples/deps/"
)
