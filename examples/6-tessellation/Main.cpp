/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#include <cmath>
#include <orhi/Backend.h>
#include <orhi/VertexBuffer.h>
#include <orhi/IndexBuffer.h>
#include <orhi/VertexArray.h>
#include <orhi/ShaderProgram.h>
#include <orhi/ShaderStage.h>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>

int main(int, char**)
{
	// GLFW setup
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "6-tessellation", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	// Graphics Backend
	orhi::Backend backend;
	backend.Init(true);
	backend.SetCapability(orhi::types::ERenderingCapability::DEPTH_TEST, true);
	backend.SetRasterizationMode(orhi::types::ERasterizationMode::LINE);

	// 3D plane patch
	const float vertices[] = {
		-2.0f, 0.0f, -2.0f, 0.0f, 0.0f,  // Bottom left
		 2.0f, 0.0f, -2.0f, 1.0f, 0.0f,  // Bottom right
		 2.0f, 0.0f,  2.0f, 1.0f, 1.0f,  // Top right
		-2.0f, 0.0f,  2.0f, 0.0f, 1.0f   // Top left
	};
	const uint32_t indices[] = { 0, 1, 2, 3 };

	// Create buffers and vertex array
	orhi::VertexBuffer vb;
	vb.Allocate(sizeof(vertices), orhi::types::EAccessSpecifier::STATIC_DRAW);
	vb.Upload(vertices);

	orhi::IndexBuffer ib;
	ib.Allocate(sizeof(indices), orhi::types::EAccessSpecifier::STATIC_DRAW);
	ib.Upload(indices);

	orhi::VertexArray va;
	va.SetLayout(std::to_array<orhi::data::VertexAttribute>({
		{ orhi::types::EDataType::FLOAT, 3 },
		{ orhi::types::EDataType::FLOAT, 2 }
	}), vb, ib);

	// Create shaders
	orhi::ShaderStage vs(orhi::types::EShaderType::VERTEX);
	vs.Upload(R"(
#version 450 core
layout(location = 0) in vec3 geo_Pos;
layout(location = 1) in vec2 geo_UV;
out vec3 vs_Position;
out vec2 vs_UV;

void main() {
	vs_Position = geo_Pos;
	vs_UV = geo_UV;
}
)");
	vs.Compile();

	orhi::ShaderStage tcs(orhi::types::EShaderType::TESSELLATION_CONTROL);
	tcs.Upload(R"(
#version 450 core
layout(vertices = 4) out;
in vec3 vs_Position[];
in vec2 vs_UV[];
out vec3 tcs_Position[];
out vec2 tcs_UV[];
uniform float u_TessellationLevel = 16.0;
uniform float u_Time;

void main() {
	tcs_Position[gl_InvocationID] = vs_Position[gl_InvocationID];
	tcs_UV[gl_InvocationID] = vs_UV[gl_InvocationID];
	
	if (gl_InvocationID == 0) {
		float tessLevel = mix(0, u_TessellationLevel, (sin(u_Time) + 1.0) / 2.0);
		gl_TessLevelOuter[0] = gl_TessLevelOuter[1] = gl_TessLevelOuter[2] = gl_TessLevelOuter[3] = tessLevel;
		gl_TessLevelInner[0] = gl_TessLevelInner[1] = tessLevel;
	}
}
)");
	tcs.Compile();

	orhi::ShaderStage tes(orhi::types::EShaderType::TESSELLATION_EVALUATION);
	tes.Upload(R"(
#version 450 core
layout(quads, equal_spacing, ccw) in;
in vec3 tcs_Position[];
in vec2 tcs_UV[];
out vec2 tes_UV;
out vec3 tes_WorldPos;
uniform float u_Time = 0.0;
uniform mat4 u_ViewProjection;

vec3 interpolate3D(vec3 v0, vec3 v1, vec3 v2, vec3 v3, vec2 coord) {
	return mix(mix(v0, v1, coord.x), mix(v3, v2, coord.x), coord.y);
}

vec2 interpolate2D(vec2 v0, vec2 v1, vec2 v2, vec2 v3, vec2 coord) {
	return mix(mix(v0, v1, coord.x), mix(v3, v2, coord.x), coord.y);
}

void main() {
	vec3 position = interpolate3D(tcs_Position[0], tcs_Position[1], tcs_Position[2], tcs_Position[3], gl_TessCoord.xy);
	tes_UV = interpolate2D(tcs_UV[0], tcs_UV[1], tcs_UV[2], tcs_UV[3], gl_TessCoord.xy);
	
	// Wave deformation
	position.y = sin(position.x * 2.0 + u_Time * 1.5) * 0.5 + cos(position.z * 2.0 + u_Time) * 0.3;
	
	tes_WorldPos = position;
	gl_Position = u_ViewProjection * vec4(position, 1.0);
}
)");
	tes.Compile();

	orhi::ShaderStage fs(orhi::types::EShaderType::FRAGMENT);
	fs.Upload(R"(
#version 450 core
in vec2 tes_UV;
in vec3 tes_WorldPos;
out vec4 FragColor;

void main() {
	float height = (tes_WorldPos.y + 1.0) * 0.5;
	vec3 color = mix(vec3(0.2, 0.2, 1.0), vec3(1.0, 0.2, 0.2), height);
	FragColor = vec4(color, 1.0);
}
)");
	fs.Compile();

	// Create and link shader program
	orhi::ShaderProgram program;
	program.Attach(vs);
	program.Attach(tcs);
	program.Attach(tes);
	program.Attach(fs);
	program.Link();

	// Render loop
	while (!glfwWindowShouldClose(window)) {
		float currentTime = static_cast<float>(glfwGetTime());

		int width, height;
		glfwGetFramebufferSize(window, &width, &height);
		backend.SetViewport(0, 0, width, height);
		backend.Clear(true, true, true);

		// Create view-projection matrix
		const glm::mat4 proj = glm::perspective(glm::radians(60.0f), (float)width / height, 0.1f, 100.0f);
		const glm::mat4 view = glm::lookAt(glm::vec3(5.0f, 0.0f, 0.0f), glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		const glm::mat4 viewProj = proj * view;

		// Render
		program.Bind();
		program.SetUniform("u_Time", currentTime);
		program.SetUniform("u_TessellationLevel", 64.0f);
		program.SetUniform("u_ViewProjection", reinterpret_cast<const orhi::math::Mat4&>(viewProj));
		va.Bind();
		backend.DrawElements(orhi::types::EPrimitiveMode::PATCHES, 4);
		va.Unbind();
		program.Unbind();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();

	return EXIT_SUCCESS;
}
