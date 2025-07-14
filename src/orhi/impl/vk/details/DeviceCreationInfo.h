/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#if defined(ORHI_COMPILE_VULKAN)

#include <orhi/impl/vk/details/QueueFamilyIndices.h>
#include <orhi/impl/vk/details/SwapChainUtils.h>

#include <vulkan/vulkan.h>

#include <span>
#include <string>
#include <vector>

namespace orhi::impl::vk::details
{
	struct DeviceCreationInfo
	{
		VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
		VkPhysicalDeviceProperties properties;
		VkPhysicalDeviceFeatures features;
		QueueFamilyIndices queueFamilyIndices;
		SwapChainSupportDetails swapChainSupportDetails;
		std::vector<const char*> extensions;
	};
}

#endif // #if defined(ORHI_COMPILE_VULKAN)
