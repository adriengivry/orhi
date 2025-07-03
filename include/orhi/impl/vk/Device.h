/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <memory>
#include <vector>
#include <orhi/api/TDevice.h>

struct VkPhysicalDevice_T;
typedef VkPhysicalDevice_T* VkPhysicalDevice;

struct VkDevice_T;
typedef VkDevice_T* VkDevice;

struct VkQueue_T;
typedef VkQueue_T* VkQueue;

struct VkPhysicalDeviceProperties;
struct VkPhysicalDeviceFeatures;

namespace orhi::impl::vk
{
	namespace details
	{
		struct QueueFamilyIndices;
		struct SwapChainSupportDetails;
	}

	struct DeviceContext
	{
		VkDevice device = nullptr;
		VkQueue graphicsQueue = nullptr;
		VkQueue presentQueue = nullptr;
		VkPhysicalDevice physicalDevice = nullptr;
		std::unique_ptr<VkPhysicalDeviceProperties> properties;
		std::unique_ptr<VkPhysicalDeviceFeatures> features;
		std::unique_ptr<details::QueueFamilyIndices> queueFamilyIndices;
		std::unique_ptr<details::SwapChainSupportDetails> swapChainSupportDetails;
		std::vector<const char*> extensions;
	};

	using Device = api::TDevice<types::EGraphicsBackend::VULKAN, DeviceContext>;
}
