/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/apii/TDescriptorSetLayout.h>

namespace orhi::impl::vk
{
	struct DescriptorSetLayoutContext {};
	using DescriptorSetLayout = apii::TDescriptorSetLayout<types::EGraphicsBackend::VULKAN, DescriptorSetLayoutContext>;
}
