#version 450 core

layout(location = 0) in vec2 uv;

layout(location = 0) out vec4 outColor;

void main()
{
	vec3 color = vec3(1.0);
	outColor = vec4(color, 1.0);
}