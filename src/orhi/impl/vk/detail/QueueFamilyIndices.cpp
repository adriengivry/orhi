/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#if defined(ORHI_COMPILE_VULKAN)

#include <orhi/impl/vk/detail/QueueFamilyIndices.h>

#include <orhi/debug/Assert.h>

#include <set>

namespace orhi::impl::vk::detail
{
	detail::QueueFamilyIndices QueueFamilyIndices::Create(VkPhysicalDevice device, VkSurfaceKHR p_surface)
	{
		detail::QueueFamilyIndices indices;

		uint32_t queueFamilyCount = 0;
		vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

		std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
		vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

		uint32_t i = 0;

		for (const auto& queueFamily : queueFamilies)
		{
			// Early exit if all family queues have been identified
			if (indices.IsComplete())
			{
				break;
			}

			// Vulkan requires implementations that support graphics operations to have at least
			// one queue family that supports both graphics and compute operations.
			if ((queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) && (queueFamily.queueFlags & VK_QUEUE_COMPUTE_BIT))
			{
				indices.graphicsAndComputeFamily = i;
			}

			VkBool32 presentSupport = false;
			vkGetPhysicalDeviceSurfaceSupportKHR(device, i, p_surface, &presentSupport);
			if (presentSupport)
			{
				indices.presentFamily = i;
			}

			++i;
		}

		return indices;
	}

	bool QueueFamilyIndices::IsComplete() const
	{
		return graphicsAndComputeFamily && presentFamily;
	}

	std::vector<uint32_t> QueueFamilyIndices::GetUniqueQueueIndices() const
	{
		ORHI_ASSERT(IsComplete(), "Incomplete queue family indices");

		std::set<uint32_t> uniqueIndices{
			graphicsAndComputeFamily.value(),
			presentFamily.value()
		};

		std::vector<uint32_t> output;
		output.reserve(uniqueIndices.size());

		for (uint32_t index : uniqueIndices)
		{
			output.push_back(index);
		}

		return output;
	}
}

#endif // #if defined(ORHI_COMPILE_VULKAN)
