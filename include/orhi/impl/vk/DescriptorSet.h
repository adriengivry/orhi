/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/api/TDescriptorSet.h>

namespace orhi::impl::vk
{
	struct DescriptorSetContext {};
	using DescriptorSet = api::TDescriptorSet<types::EGraphicsBackend::VULKAN, DescriptorSetContext>;
}
