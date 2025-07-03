/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/api/TQueue.h>

namespace orhi::impl::vk
{
	struct QueueContext {};
	using Queue = api::TQueue<types::EGraphicsBackend::VULKAN, QueueContext>;
}
