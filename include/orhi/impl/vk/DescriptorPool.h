/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/api/TDescriptorPool.h>

namespace orhi::impl::vk
{
	struct DescriptorPoolContext {};
	using DescriptorPool = api::TDescriptorPool<types::EGraphicsBackend::VULKAN, DescriptorPoolContext>;
}
