/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/apii/TSemaphore.h>

namespace orhi::impl::vk
{
	struct SemaphoreContext {};
	using Semaphore = apii::TSemaphore<types::EGraphicsBackend::VULKAN, SemaphoreContext>;
}
