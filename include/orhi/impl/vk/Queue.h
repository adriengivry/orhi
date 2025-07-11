/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/api/TQueue.h>

struct VkDevice_T;
typedef VkDevice_T* VkDevice;

struct VkQueue_T;
typedef VkQueue_T* VkQueue;

namespace orhi::impl::vk
{
	struct QueueContext
	{
		VkDevice device;
		VkQueue handle;
	};

	using Queue = api::TQueue<types::EGraphicsBackend::VULKAN, CTX_SIG_DEF>;
}
