#version 450 core

layout(location = 0) in vec3 normal;

layout(location = 0) out vec4 outColor;

void main()
{
	float light = max(dot(normal, vec3(0.0, 0.5, 0.5)), 0.2);
	outColor = vec4(vec3(1.0) * light, 1.0);
}