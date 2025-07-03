/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/api/TSemaphore.h>

namespace orhi::impl::vk
{
	struct SemaphoreContext {};
	using Semaphore = api::TSemaphore<types::EGraphicsBackend::VULKAN, SemaphoreContext>;
}
