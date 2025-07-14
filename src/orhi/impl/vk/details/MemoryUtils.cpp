/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#if defined(ORHI_COMPILE_VULKAN)

#include <orhi/impl/vk/details/MemoryUtils.h>

#include <orhi/debug/Assert.h>

namespace orhi::impl::vk::details
{
	uint32_t MemoryUtils::FindMemoryType(VkPhysicalDevice p_physicalDevice, uint32_t p_typeFilter, VkMemoryPropertyFlags p_properties)
	{
		VkPhysicalDeviceMemoryProperties memProperties;
		vkGetPhysicalDeviceMemoryProperties(p_physicalDevice, &memProperties);

		for (uint32_t i = 0; i < memProperties.memoryTypeCount; i++)
		{
			if ((p_typeFilter & (1 << i)) && (memProperties.memoryTypes[i].propertyFlags & p_properties) == p_properties)
			{
				return i;
			}
		}

		ORHI_ASSERT(false, "failed to find suitable memory type!");
		return {};
	}
}

#endif // #if defined(ORHI_COMPILE_VULKAN)
