/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/api/TDescriptorSetLayout.h>
#include <orhi/impl/vk/Device.h>

struct VkDescriptorSetLayout_T;
typedef VkDescriptorSetLayout_T* VkDescriptorSetLayout;

namespace orhi::impl::vk
{
	struct DescriptorSetLayoutContext
	{
		Device& device;
		VkDescriptorSetLayout handle;
	};

	using DescriptorSetLayout = api::TDescriptorSetLayout<types::EGraphicsBackend::VULKAN, DescriptorSetLayoutContext, DeviceContext>;
}
