/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <string>
#include <span>
#include <vector>
#include <orhi/impl/vk/details/SwapChainUtils.h>
#include <orhi/impl/vk/details/QueueFamilyIndices.h>
#include <vulkan/vulkan.h>

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
