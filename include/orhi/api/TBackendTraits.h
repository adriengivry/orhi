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
	/**
	* @brief Backend traits structure that defines type mappings for a specific graphics backend
	* 
	* This template structure serves as a type trait system that maps generic OpenRHI types
	* to backend-specific implementation types. Each graphics backend (Vulkan, DirectX, etc.)
	* provides its own specialization of this traits struct.
	*/
	template<
		types::EGraphicsBackend BackendType,
		typename TBackendContext,
		typename TBufferContext,
		typename TCommandBufferContext,
		typename TCommandPoolContext,
		typename TDescriptorContext,
		typename TDescriptorPoolContext,
		typename TDescriptorSetContext,
		typename TDescriptorSetLayoutContext,
		typename TDeviceContext,
		typename TFenceContext,
		typename TFramebufferContext,
		typename TPipelineContext,
		typename TPipelineLayoutContext,
		typename TQueueContext,
		typename TRenderPassContext,
		typename TSemaphoreContext,
		typename TShaderModuleContext,
		typename TSwapChainContext,
		typename TTextureContext
	>
	struct TBackendTraits
	{
		static constexpr types::EGraphicsBackend BackendType = BackendType;
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
		using PipelineContext = TPipelineContext;
		using PipelineLayoutContext = TPipelineLayoutContext;
		using QueueContext = TQueueContext;
		using RenderPassContext = TRenderPassContext;
		using SemaphoreContext = TSemaphoreContext;
		using ShaderModuleContext = TShaderModuleContext;
		using SwapChainContext = TSwapChainContext;
		using TextureContext = TTextureContext;
	};
}
