/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/
#pragma once

#include <type_traits>

namespace orhi::utils
{
	/**
	* Registry structure that agglomerates all context types for a specific backend.
	* This replaces the need to pass all individual context types as template parameters.
	*/
	template<typename TBackendContext, typename TBufferContext, typename TCommandBufferContext, 
		typename TCommandPoolContext, typename TDescriptorContext, typename TDescriptorPoolContext,
		typename TDescriptorSetContext, typename TDescriptorSetLayoutContext, typename TDeviceContext,
		typename TFenceContext, typename TFramebufferContext, typename TGraphicsPipelineContext,
		typename TQueueContext, typename TRenderPassContext, typename TSemaphoreContext,
		typename TShaderModuleContext, typename TSwapChainContext, typename TTextureContext>
	struct ContextRegistry
	{
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

#define CTX_REG_INST(name, backend, registry) \
template class orhi::api::name<backend, registry>

#define CTX_REG_INST_VK(name) CTX_REG_INST(name, orhi::types::EGraphicsBackend::VULKAN, orhi::impl::vk::VulkanContextRegistry)