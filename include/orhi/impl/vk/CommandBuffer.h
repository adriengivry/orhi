/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/api/TCommandBuffer.h>

struct VkCommandBuffer_T;
typedef VkCommandBuffer_T* VkCommandBuffer;

namespace orhi::impl::vk
{
	struct CommandBufferContext
	{
		VkCommandBuffer handle;
	};

	using CommandBuffer = api::TCommandBuffer<
		types::EGraphicsBackend::VULKAN,
		struct CommandBufferContext,
		struct DeviceContext,
		struct RenderPassContext,
		struct FramebufferContext,
		struct BufferContext,
		struct DescriptorSetContext,
		struct TextureContext,
		struct DescriptorContext
	>;
}
