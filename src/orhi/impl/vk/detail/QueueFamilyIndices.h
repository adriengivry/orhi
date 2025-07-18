/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#if defined(ORHI_COMPILE_VULKAN)

#include <vulkan/vulkan.h>

#include <optional>
#include <vector>

namespace orhi::impl::vk::detail
{
	struct QueueFamilyIndices
	{
		std::optional<uint32_t> graphicsAndComputeFamily;
		std::optional<uint32_t> presentFamily;
		
		static detail::QueueFamilyIndices Create(VkPhysicalDevice device, VkSurfaceKHR p_surface);
		bool IsComplete() const;
		std::vector<uint32_t> GetUniqueQueueIndices() const;

	private:
		QueueFamilyIndices() = default;
	};
}

#endif // #if defined(ORHI_COMPILE_VULKAN)
