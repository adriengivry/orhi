/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#if defined(ORHI_COMPILE_VULKAN)

#if defined(_WIN32) || defined(_WIN64)
#define VK_USE_PLATFORM_WIN32_KHR
#endif

#include <orhi/debug/Assert.h>
#include <orhi/debug/Log.h>
#include <orhi/impl/vk/Device.h>
#include <orhi/impl/vk/details/ExtensionManager.h>
#include <orhi/impl/vk/details/ValidationLayerManager.h>
#include <orhi/impl/vk/details/DebugMessenger.h>
#include <orhi/impl/vk/details/global/SharedContext.h>
#include <orhi/impl/vk/details/SwapChainUtils.h>
#include <orhi/impl/vk/details/DeviceCreationInfo.h>
#include <orhi/impl/vk/details/QueueFamilyIndices.h>
#include <format>
#include <optional>
#include <set>
#include <vulkan/vulkan.h>

using namespace orhi::impl::vk;

namespace
{
}

namespace orhi
{
	template<>
	Device::TDevice(const void* p_deviceCreationInfo) : m_context{
		.physicalDevice = static_cast<const details::DeviceCreationInfo*>(p_deviceCreationInfo)->physicalDevice,
		.properties = std::make_unique<VkPhysicalDeviceProperties>(static_cast<const details::DeviceCreationInfo*>(p_deviceCreationInfo)->properties),
		.features = std::make_unique<VkPhysicalDeviceFeatures>(static_cast<const details::DeviceCreationInfo*>(p_deviceCreationInfo)->features),
		.queueFamilyIndices = std::make_unique<details::QueueFamilyIndices>(static_cast<const details::DeviceCreationInfo*>(p_deviceCreationInfo)->queueFamilyIndices),
		.swapChainSupportDetails = std::make_unique<details::SwapChainSupportDetails>(static_cast<const details::DeviceCreationInfo*>(p_deviceCreationInfo)->swapChainSupportDetails),
		.extensions = static_cast<const details::DeviceCreationInfo*>(p_deviceCreationInfo)->extensions
	}
	{
		std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;

		std::set<uint32_t> uniqueQueueFamilies = {
			m_context.queueFamilyIndices->graphicsFamily.value(),
			m_context.queueFamilyIndices->presentFamily.value()
		};

		float queuePriority = 1.0f;

		for (uint32_t queueFamily : uniqueQueueFamilies)
		{
			VkDeviceQueueCreateInfo queueCreateInfo{
				.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
				.queueFamilyIndex = queueFamily,
				.queueCount = 1,
				.pQueuePriorities = &queuePriority
			};

			queueCreateInfos.push_back(queueCreateInfo);
		}

		VkDeviceCreateInfo createInfo{
			.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
			.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size()),
			.pQueueCreateInfos = queueCreateInfos.data(),
			.enabledExtensionCount = static_cast<uint32_t>(m_context.extensions.size()),
			.ppEnabledExtensionNames = m_context.extensions.data(),
			.pEnabledFeatures = m_context.features.get(),
		};

		VkResult result = vkCreateDevice(
			m_context.physicalDevice,
			&createInfo,
			nullptr,
			&m_context.device
		);

		details::global::sharedContext.device = m_context.device;

		ORHI_ASSERT(result == VK_SUCCESS, "failed to create logical device!");

		VkQueue graphicsQueue, presentQueue;
		vkGetDeviceQueue(m_context.device, m_context.queueFamilyIndices->graphicsFamily.value(), 0, &graphicsQueue);
		vkGetDeviceQueue(m_context.device, m_context.queueFamilyIndices->presentFamily.value(), 0, &presentQueue);
	}

	template<>
	Device::~TDevice()
	{
		vkDestroyDevice(
			m_context.device,
			nullptr
		);
	}

	template<>
	data::SwapChainDesc Device::GetOptimalSwapChainDesc(std::pair<uint32_t, uint32_t> p_windowSize)
	{
		auto optimalConfig = details::SwapChainUtils::CalculateSwapChainOptimalConfig(
			*m_context.swapChainSupportDetails,
			{ p_windowSize.first, p_windowSize.second }
		);

		return data::SwapChainDesc{
			.format = static_cast<types::EFormat>(optimalConfig.surfaceFormat.format)
		};
	}

	template<>
	data::NativeHandle Device::GetNativeHandle() const
	{
		return m_context.device;
	}

	template<>
	data::NativeHandle Device::GetAdapterNativeHandle() const
	{
		return m_context.physicalDevice;
	}
}

#endif // #if defined(ORHI_COMPILE_VULKAN)
