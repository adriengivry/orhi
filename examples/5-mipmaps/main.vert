#version 450

// Input
layout(location = 0) in vec2 inPosition;
layout(location = 1) in vec2 inUV;

// Output
layout(location = 0) out vec2 uv;

void main()
{
    gl_Position = vec4(inPosition, 0.0, 1.0);
    uv = inUV;
}
