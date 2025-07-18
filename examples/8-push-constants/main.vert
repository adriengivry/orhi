#version 450

layout(location = 0) out vec3 fragColor;

vec2 positions[3] = vec2[](
	vec2(-0.5, 0.5),
	vec2(0.5, 0.5),
	vec2(0.0, -0.5)
);

vec3 colors[3] = vec3[](
	vec3(1.0, 0.0, 0.0),
	vec3(0.0, 1.0, 0.0),
	vec3(0.0, 0.0, 1.0)
);

layout( push_constant ) uniform constants
{
	float time;
} PushConstants;

void main() {
	const vec2 offset = vec2(
		cos(PushConstants.time + gl_VertexIndex),
		cos(PushConstants.time - gl_VertexIndex)
	) * 0.25;

	gl_Position = vec4(positions[gl_VertexIndex] + offset, 0.0, 1.0);
	fragColor = colors[gl_VertexIndex];
}
