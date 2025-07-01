/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/apii/TDescriptorSet.h>

namespace orhi::impl::vk
{
	struct DescriptorSetContext {};
	using DescriptorSet = apii::TDescriptorSet<types::EGraphicsBackend::VULKAN, DescriptorSetContext>;
}
