/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/apii/TDescriptorPool.h>

namespace orhi::impl::vk
{
	struct DescriptorPoolContext {};
	using DescriptorPool = apii::TDescriptorPool<types::EGraphicsBackend::VULKAN, DescriptorPoolContext>;
}
