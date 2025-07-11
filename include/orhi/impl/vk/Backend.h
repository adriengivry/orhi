/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <memory>
#include <orhi/api/TBackend.h>
#include <orhi/impl/vk/ContextRegistry.h>

struct VkInstance_T;
typedef VkInstance_T* VkInstance;

struct VkDevice_T;
typedef VkDevice_T* VkDevice;

struct VkSurfaceKHR_T;
typedef VkSurfaceKHR_T* VkSurfaceKHR;

struct VkQueue_T;
typedef VkQueue_T* VkQueue;

namespace orhi::impl::vk
{
	struct BackendContext 
	{
		VkInstance instance;
		VkDevice device;
		VkSurfaceKHR surface;
		VkQueue graphicsQueue;
		VkQueue presentQueue;
	};

	struct DeviceContext;

	// Legacy type alias (deprecated)
	using Backend = api::TBackend<types::EGraphicsBackend::VULKAN, ContextRegistry>;
	
	// New type alias using ContextRegistry
	using BackendNew = api::TBackend<types::EGraphicsBackend::VULKAN, ContextRegistry>;
}
