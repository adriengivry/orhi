/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/
#pragma once

#include <type_traits>
#include <orhi/types/EGraphicsBackend.h>

namespace orhi::api
{
	/**
	* Registry structure that agglomerates all context types for a specific backend.
	*/
	template<types::EGraphicsBackend Backend, typename TBackendContext, typename TBufferContext, typename TCommandBufferContext, 
		typename TCommandPoolContext, typename TDescriptorContext, typename TDescriptorPoolContext,
		typename TDescriptorSetContext, typename TDescriptorSetLayoutContext, typename TDeviceContext,
		typename TFenceContext, typename TFramebufferContext, typename TGraphicsPipelineContext,
		typename TQueueContext, typename TRenderPassContext, typename TSemaphoreContext,
		typename TShaderModuleContext, typename TSwapChainContext, typename TTextureContext>
	struct TContextRegistry
	{
		static constexpr types::EGraphicsBackend BackendType = Backend;
		using BackendContext = TBackendContext;
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
