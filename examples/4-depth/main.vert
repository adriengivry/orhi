#version 450

// UBO
layout(binding = 0) uniform UniformBufferObject {
    mat4 model;
    mat4 view;
    mat4 proj;
    vec3 color;
} ubo;

// Input
layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inNormal;

// Output
layout(location = 0) out vec3 normal;
layout(location = 1) out vec3 color;

void main()
{
    gl_Position = ubo.proj * ubo.view * ubo.model * vec4(inPosition, 1.0);
    normal =  normalize(mat3(ubo.model) * inNormal);
    color = ubo.color;
}
