/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/api/TInstance.h>
#include <orhi/impl/vk/BackendTraits.h>

#include <cstdint>
#include <memory>

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
		uint32_t apiVersion = 0;
		VkDevice device;
		VkSurfaceKHR surface;
		VkQueue graphicsAndComputeQueue;
		VkQueue presentQueue;
	};

	using Instance = api::TInstance<BackendTraits>;
}
