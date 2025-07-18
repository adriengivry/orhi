/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/api/TFence.h>
#include <orhi/impl/vk/BackendTraits.h>
#include <orhi/impl/vk/Device.h>

struct VkFence_T;
typedef VkFence_T* VkFence;

namespace orhi::impl::vk
{
	struct FenceContext
	{
		Device& device;
	};

	using Fence = api::TFence<BackendTraits>;
}
