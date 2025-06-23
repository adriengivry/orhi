/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#include <orhi/Backend.h>
#include <orhi/VertexBuffer.h>
#include <orhi/IndexBuffer.h>
#include <orhi/VertexArray.h>
#include <orhi/ShaderProgram.h>
#include <orhi/ShaderStage.h>
#include <GLFW/glfw3.h>

int main(int, char**)
{
	// GLFW setup
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(512, 512, "4-geometry", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	// Graphics Backend
	orhi::Backend backend;
	backend.Init(true);

	// Empty vertex array - the geometry shader will generate all vertices
	orhi::VertexArray va;

	// Vertex Shader - minimal shader since we're not using vertex data
	orhi::ShaderStage vs(orhi::types::EShaderType::VERTEX);
	vs.Upload(R"(
#version 450 core
)");
	vs.Compile();

	// Geometry Shader - generates Fibonacci spiral as line segments
	orhi::ShaderStage gs(orhi::types::EShaderType::GEOMETRY);
	gs.Upload(R"(
#version 450 core

layout(points) in;
layout(line_strip, max_vertices = 200) out;

out vec3 g_Color;

#define PI 3.14159265359
#define GOLDEN_RATIO 1.618033988749

void main() {
	// Generate Fibonacci spiral entirely in geometry shader
	// No input data needed - we create everything from scratch
	vec4 center = vec4(0.0, 0.0, 0.0, 1.0);  // Fixed center point
	
	// Generate Fibonacci spiral
	float angle = 0.0;
	float radius = 0.01;
	float scale = 20.0; // Scale factor to fit in viewport
	
	// Generate points along the Fibonacci spiral
	for(int i = 0; i < 100; ++i) {
		// Calculate position using Fibonacci spiral formula
		// r = a * phi^(b*theta) where phi is golden ratio
		float spiralRadius = radius * pow(GOLDEN_RATIO, angle * 0.1) * scale;
		
		float x = center.x + spiralRadius * cos(angle);
		float y = center.y + spiralRadius * sin(angle);
		
		gl_Position = vec4(x, y, center.z, 1.0);
		
		// Color based on position in spiral (rainbow effect)
		float t = float(i) / 99.0;
		g_Color = vec3(
			0.5 + 0.5 * sin(t * 6.28 + 0.0),
			0.5 + 0.5 * sin(t * 6.28 + 2.09),
			0.5 + 0.5 * sin(t * 6.28 + 4.18)
		);
		
		EmitVertex();
		
		// Increment angle for next point
		angle += 0.3;
	}
	
	EndPrimitive();
}
)");
	gs.Compile();

	// Fragment Shader
	orhi::ShaderStage fs(orhi::types::EShaderType::FRAGMENT);
	fs.Upload(R"(
#version 450 core
in vec3 g_Color;
out vec4 FragColor;

void main() {
	FragColor = vec4(g_Color, 1.0);
}
)");
	fs.Compile();

	orhi::ShaderProgram program;
	program.Attach(vs);
	program.Attach(gs);
	program.Attach(fs);
	program.Link();

	// Render loop
	while (!glfwWindowShouldClose(window))
	{
		int width, height;
		glfwGetFramebufferSize(window, &width, &height);
		backend.SetViewport(0, 0, width, height);
		backend.Clear(true, true, true);

		program.Bind();
		va.Bind();
		backend.DrawArrays(orhi::types::EPrimitiveMode::POINTS, 1);
		va.Unbind();
		program.Unbind();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();

	return EXIT_SUCCESS;
}
