/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/apii/TBackend.h>

namespace orhi::impl::vk
{
	struct BackendContext {};
	using Backend = apii::TBackend<types::EGraphicsBackend::VULKAN, BackendContext>;
}
