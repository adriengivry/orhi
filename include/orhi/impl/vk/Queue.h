/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/apii/TQueue.h>

namespace orhi::impl::vk
{
	struct QueueContext {};
	using Queue = apii::TQueue<types::EGraphicsBackend::VULKAN, QueueContext>;
}
