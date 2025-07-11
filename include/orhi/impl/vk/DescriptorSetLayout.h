/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/api/TDescriptorSetLayout.h>
#include <orhi/impl/vk/Device.h>
#include <orhi/impl/vk/VulkanContextRegistry.h>

struct VkDescriptorSetLayout_T;
typedef VkDescriptorSetLayout_T* VkDescriptorSetLayout;

namespace orhi::impl::vk
{
	struct DescriptorSetLayoutContext
	{
		Device& device;
		VkDescriptorSetLayout handle;
	};

	using DescriptorSetLayout = api::TDescriptorSetLayout<types::EGraphicsBackend::VULKAN, VulkanContextRegistry>;
}
