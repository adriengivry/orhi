/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/
#pragma once

#include <type_traits>

#define CTX_SIG_AS(type) \
type BackendContext, \
type BufferContext, \
type CommandBufferContext, \
type CommandPoolContext, \
type DescriptorContext, \
type DescriptorPoolContext, \
type DescriptorSetContext, \
type DescriptorSetLayoutContext, \
type DeviceContext, \
type FenceContext, \
type FramebufferContext, \
type GraphicsPipelineContext, \
type QueueContext, \
type RenderPassContext, \
type SemaphoreContext, \
type ShaderModuleContext, \
type SwapChainContext, \
type TextureContext

#define CTX_SIG_NUL
#define CTX_SIG_DCL CTX_SIG_AS(class)
#define CTX_SIG_DEF CTX_SIG_AS(struct)
#define CTX_SIG_FWD CTX_SIG_AS(CTX_SIG_NUL)

// Explicit template instantiation
#define CTX_SIG_REG(name, backend, ns) \
template class orhi::api::name< \
	backend, \
	ns::BackendContext, \
	ns::BufferContext, \
	ns::CommandBufferContext, \
	ns::CommandPoolContext, \
	ns::DescriptorContext, \
	ns::DescriptorPoolContext, \
	ns::DescriptorSetContext, \
	ns::DescriptorSetLayoutContext, \
	ns::DeviceContext, \
	ns::FenceContext, \
	ns::FramebufferContext, \
	ns::GraphicsPipelineContext, \
	ns::QueueContext, \
	ns::RenderPassContext, \
	ns::SemaphoreContext, \
	ns::ShaderModuleContext, \
	ns::SwapChainContext, \
	ns::TextureContext \
>

#define CTX_SIG_REG_VK(name) CTX_SIG_REG(name, orhi::types::EGraphicsBackend::VULKAN, orhi::impl::vk)