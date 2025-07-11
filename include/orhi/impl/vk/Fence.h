/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/api/TFence.h>
#include <orhi/impl/vk/Device.h>
#include <orhi/impl/vk/ContextRegistry.h>

struct VkFence_T;
typedef VkFence_T* VkFence;

namespace orhi::impl::vk
{
	struct FenceContext
	{
		Device& device;
		VkFence handle;
	};

	using Fence = api::TFence<ContextRegistry>;
}
