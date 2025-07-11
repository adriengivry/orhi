/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/api/TDescriptorSet.h>
#include <orhi/impl/vk/Device.h>

struct VkDescriptorSet_T;
typedef VkDescriptorSet_T* VkDescriptorSet;

namespace orhi::impl::vk
{
	struct DescriptorSetContext
	{
		Device& device;
		VkDescriptorSet handle;
	};

	using DescriptorSet = api::TDescriptorSet<types::EGraphicsBackend::VULKAN, CTX_SIG_DEF>;
}
