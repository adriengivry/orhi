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

#include <orhi/Backend.h>
#include <orhi/Surface.h>
#include <orhi/DeviceManager.h>

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

	/*
	val::SurfaceDesc GetGlfwSurfaceDesc(GLFWwindow* p_window)
	{
#if defined(_WIN32) || defined(_WIN64)
		return {
			.windowHandle = glfwGetWin32Window(p_window),
			.instanceHandle = GetModuleHandle(nullptr)
		};
#else
#error Only supporting Windows for now!
#endif
	}
	*/
}

int RunVulkan(GLFWwindow* window)
{
	// Create backend
	auto backend = std::make_unique<orhi::Backend>(
		/*
		val::InstanceDesc{
			.requiredExtensions = GetGlfwRequiredExtensions()
		}
		*/
	);

	// Create surface
	auto surface = std::make_unique<orhi::Surface>(
		/*
		instance->GetHandle(),
		GetGlfwSurfaceDesc(window)
		*/
	);

	// assert((surface && surface->GetHandle() != VK_NULL_HANDLE) && "invalid surface handle, cannot continue since headless isn't supported");

	// Create device manager so we can find a suitable device
	auto deviceManager = std::make_unique<orhi::DeviceManager>(
		/*
		instance->GetHandle(),
		surface->GetHandle()
		*/
	);

	// Retrieve the most suited device
	// val::Device& device = deviceManager->GetSuitableDevice();
	// device.CreateLogicalDevice(instance->GetValidationLayers());

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
	}

	return EXIT_SUCCESS;
}

int main()
{
	glfwInit();

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
	GLFWwindow* window = glfwCreateWindow(800, 600, "0-vulkan", nullptr, nullptr);

	int exitCode = RunVulkan(window);

	glfwDestroyWindow(window);
	glfwTerminate();

	return exitCode;
}
