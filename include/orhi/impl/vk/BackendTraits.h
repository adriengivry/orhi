/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/api/TBackendTraits.h>

namespace orhi::impl::vk
{
	struct InstanceContext;
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

	using BackendTraits = orhi::api::TBackendTraits<
		orhi::types::EGraphicsBackend::VULKAN,
		InstanceContext,
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
