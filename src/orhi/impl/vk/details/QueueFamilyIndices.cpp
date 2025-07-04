/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#include <orhi/impl/vk/details/QueueFamilyIndices.h>
#include <orhi/debug/Assert.h>
#include <set>

namespace orhi::impl::vk::details
{
	details::QueueFamilyIndices QueueFamilyIndices::Create(VkPhysicalDevice device, VkSurfaceKHR p_surface)
	{
		details::QueueFamilyIndices indices;

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

			if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT)
			{
				indices.graphicsFamily = i;
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
		return graphicsFamily && presentFamily;
	}

	std::vector<uint32_t> QueueFamilyIndices::GetUniqueQueueIndices() const
	{
		ORHI_ASSERT(IsComplete(), "Incomplete queue family indices");

		std::set<uint32_t> uniqueIndices{
			graphicsFamily.value(),
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
