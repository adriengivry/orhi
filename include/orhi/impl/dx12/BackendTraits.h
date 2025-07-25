/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry, Jian Bang Xu
* @licence: MIT
*/

#pragma once

#include <orhi/api/TBackendTraits.h>

namespace orhi::impl::dx12
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
	struct PipelineContext;
	struct PipelineLayoutContext;
	struct QueueContext;
	struct RenderPassContext;
	struct SemaphoreContext;
	struct ShaderModuleContext;
	struct SwapChainContext;
	struct TextureContext;

	using BackendTraits = orhi::api::TBackendTraits<
		orhi::types::EGraphicsBackend::DIRECTX12,
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
		PipelineContext,
		PipelineLayoutContext,
		QueueContext,
		RenderPassContext,
		SemaphoreContext,
		ShaderModuleContext,
		SwapChainContext,
		TextureContext
	>;
}
