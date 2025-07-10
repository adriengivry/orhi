/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/api/TDescriptorPool.h>
#include <orhi/impl/vk/Device.h>
#include <orhi/impl/vk/DescriptorSet.h>
#include <list>

struct VkDescriptorPool_T;
typedef VkDescriptorPool_T* VkDescriptorPool;

namespace orhi::impl::vk
{
	struct DescriptorPoolContext
	{
		Device& device;
		VkDescriptorPool handle;
		std::list<DescriptorSet> descriptorSets;
	};

	using DescriptorPool = api::TDescriptorPool<
		types::EGraphicsBackend::VULKAN,
		struct DescriptorPoolContext,
		struct DeviceContext,
		struct DescriptorSetContext,
		struct DescriptorSetLayoutContext,
		struct BufferContext,
		struct DescriptorContext,
		struct TextureContext
	>;
}
