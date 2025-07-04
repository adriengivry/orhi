/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <vulkan/vulkan.h>

namespace orhi::impl::vk::details::global
{
	struct SharedContext
	{
		VkDevice device;
		VkInstance instance;
	};
	
	extern SharedContext sharedContext;
}
