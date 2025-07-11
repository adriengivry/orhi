/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/api/TSemaphore.h>
#include <orhi/impl/vk/BackendTraits.h>
#include <orhi/impl/vk/Device.h>

struct VkSemaphore_T;
typedef VkSemaphore_T* VkSemaphore;

namespace orhi::impl::vk
{
	struct SemaphoreContext
	{
		Device& device;
		VkSemaphore handle;
	};

	using Semaphore = api::TSemaphore<BackendTraits>;
}
