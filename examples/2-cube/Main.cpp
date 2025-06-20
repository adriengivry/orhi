/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#include <chrono>
#include <orhi/Backend.h>
#include <orhi/VertexBuffer.h>
#include <orhi/IndexBuffer.h>
#include <orhi/VertexArray.h>
#include <orhi/ShaderProgram.h>
#include <orhi/ShaderStage.h>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>

int main()
{
	// GLFW setup
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(640, 480, "2-cube", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	// Backend
	orhi::Backend backend;
	backend.Init(true);
	backend.SetCapability(orhi::types::ERenderingCapability::DEPTH_TEST, true);

	// Cube vertices (position, uv, normal)
	float vertices[] = {
		// Front face
		-1.0f, -1.0f,  1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		 1.0f, -1.0f,  1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		 1.0f,  1.0f,  1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		-1.0f,  1.0f,  1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		// Back face
		-1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f,
		 1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f,
		 1.0f,  1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, -1.0f,
		-1.0f,  1.0f, -1.0f, 1.0f, 1.0f, 0.0f, 0.0f, -1.0f,
		// Left face
		-1.0f, -1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
		-1.0f, -1.0f,  1.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f,
		-1.0f,  1.0f,  1.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f,
		-1.0f,  1.0f, -1.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f,
		// Right face
		 1.0f, -1.0f,  1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
		 1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
		 1.0f,  1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		 1.0f,  1.0f,  1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		 // Top face
		 -1.0f,  1.0f,  1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		  1.0f,  1.0f,  1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		  1.0f,  1.0f, -1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
		 -1.0f,  1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
		 // Bottom face
		 -1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f,
		  1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 0.0f, -1.0f, 0.0f,
		  1.0f, -1.0f,  1.0f, 1.0f, 1.0f, 0.0f, -1.0f, 0.0f,
		 -1.0f, -1.0f,  1.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f
	};

	uint32_t indices[] = {
		0, 1, 2,   0, 2, 3,     // Front
		4, 5, 6,   4, 6, 7,     // Back
		8, 9, 10,  8, 10, 11,   // Left
		12, 13, 14, 12, 14, 15, // Right
		16, 17, 18, 16, 18, 19, // Top
		20, 21, 22, 20, 22, 23  // Bottom
	};

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
			{ orhi::types::EDataType::FLOAT, 3 }, // Position
			{ orhi::types::EDataType::FLOAT, 2 }, // UV
			{ orhi::types::EDataType::FLOAT, 3 }  // Normal
			}), vb, ib
	);

	// Shaders
	orhi::ShaderStage vs(orhi::types::EShaderType::VERTEX);
	vs.Upload(R"(
#version 450 core
layout(location = 0) in vec3 geo_Pos;
layout(location = 1) in vec2 geo_UV;
layout(location = 2) in vec3 geo_Normal;
uniform mat4 u_Model = mat4(1.0);
uniform mat4 u_View = mat4(1.0);
uniform mat4 u_Projection = mat4(1.0);
out vec3 v_Normal;
void main() {
	gl_Position = u_Projection * u_View * u_Model * vec4(geo_Pos, 1.0);
	v_Normal = normalize(mat3(u_Model) * geo_Normal);
}
)");
	vs.Compile();

	orhi::ShaderStage fs(orhi::types::EShaderType::FRAGMENT);
	fs.Upload(R"(
#version 450 core
in vec3 v_Normal;
out vec4 FragColor;
uniform vec3 u_Color = vec3(1.0, 1.0, 0.0);
void main() {
	float light = max(dot(v_Normal, vec3(0.0, 0.0, 1.0)), 0.2);
	FragColor = vec4(u_Color * light, 1.0);
}
)");
	fs.Compile();

	orhi::ShaderProgram program;
	program.Attach(vs);
	program.Attach(fs);
	program.Link();

	// Camera
	glm::vec3 camPos = { 0.0f, 0.0f, 5.0f };
	auto startTime = std::chrono::steady_clock::now();

	// Render loop
	while (!glfwWindowShouldClose(window))
	{
		// Time
		auto now = std::chrono::steady_clock::now();
		float time = std::chrono::duration<float>(now - startTime).count();

		// Input
		const float speed = 0.1f;
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) camPos.z -= speed;
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) camPos.z += speed;
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) camPos.x -= speed;
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) camPos.x += speed;
		if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) camPos.y -= speed;
		if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) camPos.y += speed;
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) break;

		// Viewport
		int width, height;
		glfwGetFramebufferSize(window, &width, &height);
		backend.SetViewport(0, 0, width, height);
		backend.Clear(true, true, true);

		// Matrices
		glm::mat4 model = glm::rotate(glm::mat4(1.0f), time, glm::vec3(1.0f, 1.0f, 1.0f));
		glm::mat4 view = glm::lookAt(camPos, camPos + glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glm::mat4 proj = glm::perspective(glm::radians(60.0f), (float)width / height, 0.1f, 100.0f);

		// Draw
		program.Bind();
		program.SetUniform("u_Model", reinterpret_cast<const orhi::math::Mat4&>(model));
		program.SetUniform("u_View", reinterpret_cast<const orhi::math::Mat4&>(view));
		program.SetUniform("u_Projection", reinterpret_cast<const orhi::math::Mat4&>(proj));
		program.SetUniform("u_Color", orhi::math::Vec3{ 1.0f, 1.0f, 0.0f });

		va.Bind();
		backend.DrawElements(orhi::types::EPrimitiveMode::TRIANGLES, 36);
		va.Unbind();
		program.Unbind();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();

	return EXIT_SUCCESS;
}
