/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/api/TQueue.h>
#include <orhi/impl/vk/BackendTraits.h>

struct VkDevice_T;
typedef VkDevice_T* VkDevice;

struct VkQueue_T;
typedef VkQueue_T* VkQueue;

namespace orhi::impl::vk
{
	struct QueueContext
	{
		VkDevice device;
	};

	using Queue = api::TQueue<BackendTraits>;
}
