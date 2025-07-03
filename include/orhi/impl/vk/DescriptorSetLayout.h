/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/api/TDescriptorSetLayout.h>

namespace orhi::impl::vk
{
	struct DescriptorSetLayoutContext {};
	using DescriptorSetLayout = api::TDescriptorSetLayout<types::EGraphicsBackend::VULKAN, DescriptorSetLayoutContext>;
}
