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

	GLFWwindow* window = glfwCreateWindow(800, 600, "1-Triangle", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	// Graphics Backend
	orhi::Backend backend;
	backend.Init(true);

	// Triangle data
	const float vertices[] = {
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,	// Bottom left
		0.5f, -0.5f, 0.0f, 1.0f, 0.0f,	// Bottom right
		0.0f,  0.5f, 0.0f, 0.5f, 1.0f	// Top center
	};

	const uint32_t indices[] = { 0, 1, 2 };

	// Buffers
	orhi::VertexBuffer vb;
	vb.Allocate(sizeof(vertices), orhi::types::EAccessSpecifier::STATIC_DRAW);
	vb.Upload(vertices);

	orhi::IndexBuffer ib;
	ib.Allocate(sizeof(indices), orhi::types::EAccessSpecifier::STATIC_DRAW);
	ib.Upload(indices);

	orhi::VertexArray va;
	va.SetLayout(
		std::to_array<orhi::data::VertexAttribute>({
			{ orhi::types::EDataType::FLOAT, 3 },
			{ orhi::types::EDataType::FLOAT, 2 }
		}), vb, ib
	);

	// Shaders
	orhi::ShaderStage vs(orhi::types::EShaderType::VERTEX);
	vs.Upload(R"(
#version 450 core
layout(location = 0) in vec3 geo_Pos;
layout(location = 1) in vec2 geo_UV;
out vec2 v_UV;
void main() {
	gl_Position = vec4(geo_Pos, 1.0);
	v_UV = geo_UV;
}
)");
	vs.Compile();

	orhi::ShaderStage fs(orhi::types::EShaderType::FRAGMENT);
	fs.Upload(R"(
#version 450 core
in vec2 v_UV;
out vec4 FragColor;
void main() {
	FragColor = vec4(v_UV, 0.5, 1.0);
}
)");
	fs.Compile();

	orhi::ShaderProgram program;
	program.Attach(vs);
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
		backend.DrawElements(orhi::types::EPrimitiveMode::TRIANGLES, 3);
		va.Unbind();
		program.Unbind();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();

	return EXIT_SUCCESS;
}
