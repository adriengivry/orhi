/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/api/TCommandBuffer.h>
#include <orhi/impl/vk/Device.h>
#include <orhi/impl/vk/RenderPass.h>
#include <orhi/impl/vk/Framebuffer.h>
#include <orhi/impl/vk/Buffer.h>
#include <orhi/impl/vk/DescriptorSet.h>
#include <orhi/impl/vk/Texture.h>

struct VkCommandBuffer_T;
typedef VkCommandBuffer_T* VkCommandBuffer;

namespace orhi::impl::vk
{
	struct CommandBufferContext
	{
		VkCommandBuffer handle;
	};

	struct DescriptorContext;

	using CommandBuffer = api::TCommandBuffer<
		types::EGraphicsBackend::VULKAN,
		CommandBufferContext,
		DeviceContext,
		RenderPassContext,
		FramebufferContext,
		BufferContext,
		DescriptorSetContext,
		TextureContext,
		DescriptorContext
	>;
}
