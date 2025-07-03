/**
* @project: vulkan-sandbox
* @author: Adrien Givry
* @licence: MIT
*/

#include <GLFW/glfw3.h>

#if defined(_WIN32) || defined(_WIN64)
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>
#endif

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

#include <cassert>
#include <iostream>
#include <vector>
#include <span>
#include <ranges>
#include <filesystem>
#include <fstream>

#include <orhi/Backend.h>
#include <orhi/RenderPass.h>
#include <orhi/ShaderModule.h>

namespace
{
	std::pair<uint32_t, uint32_t> GetWindowSize(GLFWwindow* p_window)
	{
		int width, height;
		glfwGetFramebufferSize(p_window, &width, &height);
		return {
			static_cast<uint32_t>(width),
			static_cast<uint32_t>(height)
		};
	}

	std::vector<std::string> GetGlfwRequiredExtensions()
	{
		uint32_t glfwExtensionCount = 0;
		const char** glfwExtensions;
		glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

		std::vector<std::string> requiredExtensions;
		requiredExtensions.reserve(glfwExtensionCount);
		for (uint32_t i = 0; i < glfwExtensionCount; ++i)
		{
			requiredExtensions.push_back(glfwExtensions[i]);
		}

		return requiredExtensions;
	}

	std::vector<std::byte> ReadShaderFile(const std::filesystem::path p_fileName)
	{
		assert(std::filesystem::exists(p_fileName));

		std::ifstream file(p_fileName, std::ios::ate | std::ios::binary);

		if (!file.is_open())
		{
			throw std::runtime_error("failed to open shader file: " + p_fileName.string());
		}

		size_t fileSize = static_cast<size_t>(file.tellg());
		std::vector<std::byte> buffer(fileSize);
		file.seekg(0);
		file.read(reinterpret_cast<char*>(buffer.data()), fileSize);
		file.close();
		return buffer;
	}
}

int main()
{
	glfwInit();

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
	GLFWwindow* window = glfwCreateWindow(800, 600, "0-vulkan", nullptr, nullptr);

	// Create backend
	auto backend = std::make_unique<orhi::Backend>(
		orhi::data::BackendDesc{
			.debug = true,
			.extensions = GetGlfwRequiredExtensions(),
			.win32_windowHandle = glfwGetWin32Window(window),
			.win32_instanceHandle = GetModuleHandle(nullptr)
		}
	);

	// Make sure there is at least one suitable device
	const auto& devices = backend->GetSuitableDevices();

	assert(!devices.empty());

	// Select the first suitable device
	auto& device = backend->CreateDevice(devices.front().id);

	auto optimalSwapChainDesc = device.GetOptimalSwapChainDesc(
		GetWindowSize(window)
	);

	auto renderPass = std::make_unique<orhi::RenderPass>(
		device,
		optimalSwapChainDesc.format
	);

	auto vertexShaderModule = std::make_unique<orhi::ShaderModule>(
		device,
		ReadShaderFile("assets/shaders/main.vert.spv")
	);

	auto fragmentShaderModule = std::make_unique<orhi::ShaderModule>(
		device,
		ReadShaderFile("assets/shaders/main.frag.spv")
	);

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();

	return EXIT_SUCCESS;
}
