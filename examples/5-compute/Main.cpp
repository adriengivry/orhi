/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#include <array>
#include <orhi/Backend.h>
#include <orhi/VertexBuffer.h>
#include <orhi/IndexBuffer.h>
#include <orhi/VertexArray.h>
#include <orhi/ShaderProgram.h>
#include <orhi/ShaderStage.h>
#include <orhi/ShaderStorageBuffer.h>
#include <GLFW/glfw3.h>

struct Particle
{
	orhi::math::Vec2 position = { 0.0f, 0.0f };
	orhi::math::Vec2 velocity = { 0.0f, 0.0f };
	float life = 0.0f;

	// std430 requires the struct to be aligned based on the largest element (vec2: 8 bytes),
	// so adding a padding changes the struct size from 20 to 24 (multiple of 8).
	float padding = 0.0f; 
};

int main(int, char**)
{
	// GLFW setup
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(600, 600, "5-compute", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	// Graphics Backend
	orhi::Backend backend;
	backend.Init(true);

	constexpr uint32_t k_particleCount = 4096;
	std::vector<Particle> particles(k_particleCount); // Heap allocated, due to its size.

	// Storage buffer for particles
	orhi::ShaderStorageBuffer particleBuffer;
	particleBuffer.Allocate(particles.size() * sizeof(Particle), orhi::types::EAccessSpecifier::DYNAMIC_DRAW);
	particleBuffer.Upload(particles.data());

	// Quad for rendering particles (instanced) - made slightly larger for visibility
	constexpr float quadVertices[] = {
		-0.005f, -0.005f,
		 0.005f, -0.005f,
		 0.005f,  0.005f,
		-0.005f,  0.005f
	};
	constexpr uint32_t quadIndices[] = { 0, 1, 2, 0, 2, 3 };

	orhi::VertexBuffer vb;
	vb.Allocate(sizeof(quadVertices), orhi::types::EAccessSpecifier::STATIC_DRAW);
	vb.Upload(quadVertices);

	orhi::IndexBuffer ib;
	ib.Allocate(sizeof(quadIndices), orhi::types::EAccessSpecifier::STATIC_DRAW);
	ib.Upload(quadIndices);

	orhi::VertexArray va;
	va.SetLayout(
		std::to_array<orhi::data::VertexAttribute>({
			{ orhi::types::EDataType::FLOAT, 2 }
		}), vb, ib
	);

	// Compute shader for particle simulation
	orhi::ShaderStage computeShader(orhi::types::EShaderType::COMPUTE);
	computeShader.Upload(R"(
#version 450 core
layout(local_size_x = 64, local_size_y = 1, local_size_z = 1) in;

struct Particle {
	vec2 position;
	vec2 velocity;
	float life;
};

layout(std430, binding = 0) restrict buffer ParticleBuffer {
	 Particle particles[];
};

uniform float u_DeltaTime;
uniform float u_Time;

// Simple pseudo-random function
float random(vec2 st) {
	return fract(sin(dot(st.xy, vec2(12.9898, 78.233))) * 43758.5453123);
}

void main() {
	uint index = gl_GlobalInvocationID.x;
	if (index >= particles.length()) return;
	
	// Update particle position
	particles[index].position += particles[index].velocity * u_DeltaTime;
	
	// Decrease life
	particles[index].life -= u_DeltaTime;
	
	// Respawn particle if dead
	if (particles[index].life <= 0.0)
	{
		// Reset to center
		particles[index].position = vec2(0.0, 0.0);
		
		// Generate random angle for initial velocity
		vec2 seed = vec2(float(index), u_Time + float(index));
		float angle = random(seed) * 6.28318530718; // 2 * PI
		float speed = 0.1 + random(seed + vec2(1.0, 0.0)) * 0.2; // Speed between 0.1 and 0.3
		
		particles[index].velocity = vec2(
			cos(angle) * speed,
			sin(angle) * speed
		);
		
		// Random lifetime between 2 and 5 seconds
		particles[index].life = 2.0 + random(seed + vec2(0.0, 1.0)) * 3.0;
	}
	
	// Add gravity effect
	particles[index].velocity.y -= 0.05 * u_DeltaTime;
	
	// Add air resistance
	particles[index].velocity *= 0.999;
}
)");
	computeShader.Compile();

	orhi::ShaderProgram computeProgram;
	computeProgram.Attach(computeShader);
	computeProgram.Link();

	// Rendering shaders
	orhi::ShaderStage vertexShader(orhi::types::EShaderType::VERTEX);
	vertexShader.Upload(R"(
#version 450 core
layout(location = 0) in vec2 a_Position;

struct Particle {
	vec2 position;
	vec2 velocity;
	float life;
};

layout(std430, binding = 0) restrict readonly buffer ParticleBuffer {
	Particle particles[];
};

out float v_Life;
out float v_MaxLife;

void main() {
	vec2 particlePos = particles[gl_InstanceID].position;
	vec2 worldPos = a_Position + particlePos;
	
	gl_Position = vec4(worldPos, 0.0, 1.0);
	v_Life = particles[gl_InstanceID].life;
	v_MaxLife = 5.0; // Maximum possible lifetime
}
)");
	vertexShader.Compile();

	orhi::ShaderStage fragmentShader(orhi::types::EShaderType::FRAGMENT);
	fragmentShader.Upload(R"(
#version 450 core
in float v_Life;
in float v_MaxLife;
out vec4 FragColor;

void main() {
	// Skip dead particles
	if (v_Life <= 0.0) discard;
	
	// Calculate alpha based on remaining life
	float alpha = clamp(v_Life / v_MaxLife, 0.0, 1.0);
	
	// Color transition: white -> red as particle dies
	vec3 color = mix(vec3(1.0, 0.0, 0.0), vec3(1.0, 1.0, 1.0), alpha);
	
	FragColor = vec4(color, alpha * 0.8);
}
)");
	fragmentShader.Compile();

	orhi::ShaderProgram renderProgram;
	renderProgram.Attach(vertexShader);
	renderProgram.Attach(fragmentShader);
	renderProgram.Link();

	// Enable blending
	backend.SetCapability(orhi::types::ERenderingCapability::BLEND, true);
	backend.SetBlendingFunction(orhi::types::EBlendingFactor::SRC_ALPHA, orhi::types::EBlendingFactor::ONE_MINUS_SRC_ALPHA);

	// Timing
	float lastTime = static_cast<float>(glfwGetTime());

	// Render loop
	while (!glfwWindowShouldClose(window))
	{
		float currentTime = static_cast<float>(glfwGetTime());
		float deltaTime = currentTime - lastTime;
		lastTime = currentTime;

		int width, height;
		glfwGetFramebufferSize(window, &width, &height);
		backend.SetViewport(0, 0, width, height);
		backend.Clear(true, true, true);

		// Compute shader dispatch
		computeProgram.Bind();
		particleBuffer.Bind(0);
		computeProgram.SetUniform("u_DeltaTime", deltaTime);
		computeProgram.SetUniform("u_Time", currentTime);
		constexpr uint32_t k_workGroupSize = 64;
		constexpr uint32_t k_dispatchSize = (k_particleCount + k_workGroupSize - 1) / k_workGroupSize;
		backend.DispatchCompute(k_dispatchSize, 1, 1);
		backend.MemoryBarrier(orhi::types::EMemoryBarrierFlags::SHADER_STORAGE);

		// Render particles
		renderProgram.Bind();
		particleBuffer.Bind(0);
		va.Bind();
		backend.DrawElementsInstanced(orhi::types::EPrimitiveMode::TRIANGLES, 6, k_particleCount);
		va.Unbind();
		renderProgram.Unbind();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();

	return EXIT_SUCCESS;
}
