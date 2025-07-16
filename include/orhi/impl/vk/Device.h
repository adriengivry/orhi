/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/api/TDevice.h>
#include <orhi/data/DeviceInfo.h>
#include <orhi/impl/vk/BackendTraits.h>
#include <orhi/impl/vk/Queue.h>

#include <memory>
#include <vector>

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
	namespace detail
	{
		struct QueueFamilyIndices;
		struct SwapChainSupportDetails;
	}

	struct DeviceContext
	{
		VkPhysicalDevice physicalDevice = nullptr;
		data::DeviceInfo deviceInfo;
		std::unique_ptr<Queue> graphicsQueue;
		std::unique_ptr<Queue> presentQueue;
		std::unique_ptr<VkPhysicalDeviceProperties> properties;
		std::unique_ptr<VkPhysicalDeviceFeatures> features;
		std::unique_ptr<detail::QueueFamilyIndices> queueFamilyIndices;
		std::unique_ptr<detail::SwapChainSupportDetails> swapChainSupportDetails;
		std::vector<const char*> extensions;
	};

	using Device = api::TDevice<BackendTraits>;
}
