/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/api/TInstance.h>
#include <orhi/impl/vk/BackendTraits.h>

#include <memory>

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
	struct InstanceContext 
	{
		VkInstance instance;
		VkDevice device;
		VkSurfaceKHR surface;
		VkQueue graphicsQueue;
		VkQueue presentQueue;
	};

	using Instance = api::TInstance<BackendTraits>;
}
