/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/
#pragma once

#include <orhi/types/EGraphicsBackend.h>

#include <type_traits>

namespace orhi::api
{
	template<types::EGraphicsBackend Instance, typename TBackendContext, typename TBufferContext, typename TCommandBufferContext, 
		typename TCommandPoolContext, typename TDescriptorContext, typename TDescriptorPoolContext,
		typename TDescriptorSetContext, typename TDescriptorSetLayoutContext, typename TDeviceContext,
		typename TFenceContext, typename TFramebufferContext, typename TGraphicsPipelineContext,
		typename TQueueContext, typename TRenderPassContext, typename TSemaphoreContext,
		typename TShaderModuleContext, typename TSwapChainContext, typename TTextureContext>
	struct TBackendTraits
	{
		static constexpr types::EGraphicsBackend BackendType = Instance;
		using InstanceContext = TBackendContext;
		using BufferContext = TBufferContext;
		using CommandBufferContext = TCommandBufferContext;
		using CommandPoolContext = TCommandPoolContext;
		using DescriptorContext = TDescriptorContext;
		using DescriptorPoolContext = TDescriptorPoolContext;
		using DescriptorSetContext = TDescriptorSetContext;
		using DescriptorSetLayoutContext = TDescriptorSetLayoutContext;
		using DeviceContext = TDeviceContext;
		using FenceContext = TFenceContext;
		using FramebufferContext = TFramebufferContext;
		using GraphicsPipelineContext = TGraphicsPipelineContext;
		using QueueContext = TQueueContext;
		using RenderPassContext = TRenderPassContext;
		using SemaphoreContext = TSemaphoreContext;
		using ShaderModuleContext = TShaderModuleContext;
		using SwapChainContext = TSwapChainContext;
		using TextureContext = TTextureContext;
	};
}
