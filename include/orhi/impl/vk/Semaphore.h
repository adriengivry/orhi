/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/api/TSemaphore.h>
#include <orhi/impl/vk/BackendTraits.h>
#include <orhi/impl/vk/Device.h>

namespace orhi::impl::vk
{
	struct SemaphoreContext
	{
		Device& device;
	};

	using Semaphore = api::TSemaphore<BackendTraits>;
}
