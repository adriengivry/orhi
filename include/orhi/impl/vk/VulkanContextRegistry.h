/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/utils/ContextRegistry.h>

namespace orhi::impl::vk
{
	struct BackendContext;
	struct BufferContext;
	struct CommandBufferContext;
	struct CommandPoolContext;
	struct DescriptorContext;
	struct DescriptorPoolContext;
	struct DescriptorSetContext;
	struct DescriptorSetLayoutContext;
	struct DeviceContext;
	struct FenceContext;
	struct FramebufferContext;
	struct GraphicsPipelineContext;
	struct QueueContext;
	struct RenderPassContext;
	struct SemaphoreContext;
	struct ShaderModuleContext;
	struct SwapChainContext;
	struct TextureContext;

	using VulkanContextRegistry = orhi::utils::ContextRegistry<
		BackendContext,
		BufferContext,
		CommandBufferContext,
		CommandPoolContext,
		DescriptorContext,
		DescriptorPoolContext,
		DescriptorSetContext,
		DescriptorSetLayoutContext,
		DeviceContext,
		FenceContext,
		FramebufferContext,
		GraphicsPipelineContext,
		QueueContext,
		RenderPassContext,
		SemaphoreContext,
		ShaderModuleContext,
		SwapChainContext,
		TextureContext
	>;
}
