/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/api/TQueue.h>

struct VkDevice_T;
typedef VkDevice_T* VkDevice;

struct VkQueue_T;
typedef VkQueue_T* VkQueue;

namespace orhi::impl::vk
{
	struct DeviceContext;
	struct RenderPassContext;
	struct FramebufferContext;
	struct BufferContext;
	struct DescriptorSetContext;
	struct SwapChainContext;
	struct SemaphoreContext;
	struct FenceContext;
	struct CommandBufferContext;
	struct TextureContext;
	struct DescriptorContext;

	struct QueueContext
	{
		VkDevice device;
		VkQueue handle;
	};

	using Queue = api::TQueue<
		types::EGraphicsBackend::VULKAN,
		QueueContext,
		DeviceContext,
		RenderPassContext,
		FramebufferContext,
		BufferContext,
		DescriptorSetContext,
		SwapChainContext,
		SemaphoreContext,
		FenceContext,
		CommandBufferContext,
		TextureContext,
		DescriptorContext
	>;
}
