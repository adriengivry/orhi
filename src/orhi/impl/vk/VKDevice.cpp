/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#if defined(ORHI_COMPILE_VULKAN)

#include <orhi/impl/vk/Device.h>

#include <orhi/debug/Assert.h>
#include <orhi/debug/Log.h>
#include <orhi/impl/vk/detail/DebugMessenger.h>
#include <orhi/impl/vk/detail/DeviceCreationInfo.h>
#include <orhi/impl/vk/detail/ExtensionManager.h>
#include <orhi/impl/vk/detail/QueueFamilyIndices.h>
#include <orhi/impl/vk/detail/SwapChainUtils.h>
#include <orhi/impl/vk/detail/Types.h>
#include <orhi/impl/vk/detail/ValidationLayerManager.h>

#include <vulkan/vulkan.h>

#include <format>
#include <optional>
#include <set>

using namespace orhi::impl::vk;

namespace orhi
{
	template<>
	Device::TDevice(
		const data::DeviceInfo& p_deviceInfo,
		const void* p_deviceCreationInfo
	) : m_context{
		.physicalDevice = static_cast<const detail::DeviceCreationInfo*>(p_deviceCreationInfo)->physicalDevice,
		.deviceInfo = p_deviceInfo,
		.properties = std::make_unique<VkPhysicalDeviceProperties>(static_cast<const detail::DeviceCreationInfo*>(p_deviceCreationInfo)->properties),
		.features = std::make_unique<VkPhysicalDeviceFeatures>(static_cast<const detail::DeviceCreationInfo*>(p_deviceCreationInfo)->features),
		.queueFamilyIndices = std::make_unique<detail::QueueFamilyIndices>(static_cast<const detail::DeviceCreationInfo*>(p_deviceCreationInfo)->queueFamilyIndices),
		.swapChainSupportDetails = std::make_unique<detail::SwapChainSupportDetails>(static_cast<const detail::DeviceCreationInfo*>(p_deviceCreationInfo)->swapChainSupportDetails),
		.extensions = static_cast<const detail::DeviceCreationInfo*>(p_deviceCreationInfo)->extensions
	}
	{
		std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;

		std::set<uint32_t> uniqueQueueFamilies = {
			m_context.queueFamilyIndices->graphicsAndComputeFamily.value(),
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
			&m_handle.ReinterpretAs<VkDevice&>()
		);

		ORHI_ASSERT(result == VK_SUCCESS, "failed to create logical device!");

		VkQueue graphicsAndComputeQueue, presentQueue;
		vkGetDeviceQueue(m_handle.As<VkDevice>(), m_context.queueFamilyIndices->graphicsAndComputeFamily.value(), 0, &graphicsAndComputeQueue);
		vkGetDeviceQueue(m_handle.As<VkDevice>(), m_context.queueFamilyIndices->presentFamily.value(), 0, &presentQueue);

		m_context.graphicsAndComputeQueue = std::unique_ptr<Queue>(new Queue(
			m_handle.As<VkDevice>(),
			graphicsAndComputeQueue
		));

		m_context.presentQueue = std::unique_ptr<Queue>(new Queue(
			m_handle.As<VkDevice>(),
			presentQueue
		));
	}

	template<>
	Device::~TDevice()
	{
		m_context.graphicsAndComputeQueue.reset();
		m_context.presentQueue.reset();

		vkDestroyDevice(
			m_handle.As<VkDevice>(),
			nullptr
		);
	}

	Queue& Device::GetGraphicsAndComputeQueue() const
	{
		return *m_context.graphicsAndComputeQueue;
	}

	Queue& Device::GetPresentQueue() const
	{
		return *m_context.presentQueue;
	}

	template<>
	data::SwapChainDesc Device::GetOptimalSwapChainDesc(const math::Extent2D& p_windowSize)
	{
		auto optimalConfig = detail::SwapChainUtils::CalculateSwapChainOptimalConfig(
			*m_context.swapChainSupportDetails,
			reinterpret_cast<const VkExtent2D&>(p_windowSize)
		);

		return data::SwapChainDesc{
			.format = static_cast<types::EFormat>(optimalConfig.surfaceFormat.format),
			.colorSpace = utils::ValueToEnum<types::EColorSpace>(optimalConfig.surfaceFormat.colorSpace),
			.presentMode = utils::ValueToEnum<types::EPresentMode>(optimalConfig.presentMode),
			.currentTransform = utils::ValueToEnum<types::ESurfaceTransformFlags>(
				static_cast<VkSurfaceTransformFlagsKHR>(optimalConfig.capabilities.currentTransform)
			),
			.minImageCount = optimalConfig.capabilities.minImageCount,
			.maxImageCount = optimalConfig.capabilities.maxImageCount
		};
	}

	template<>
	data::QueuesDesc Device::GetQueuesDesc() const
	{
		return data::QueuesDesc{
			.indices = m_context.queueFamilyIndices->GetUniqueQueueIndices()
		};
	}

	template<>
	void Device::WaitIdle() const
	{
		vkDeviceWaitIdle(m_handle.As<VkDevice>());
	}

	template<>
	const data::DeviceInfo& Device::GetInfo() const
	{
		return m_context.deviceInfo;
	}

	template<>
	impl::common::NativeHandle Device::GetAdapterNativeHandle() const
	{
		return m_context.physicalDevice;
	}
}

template class orhi::api::TDevice<orhi::impl::vk::BackendTraits>;

#endif // #if defined(ORHI_COMPILE_VULKAN)
