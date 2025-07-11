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
	orhi::types::EGraphicsBackend::backend, \
	orhi::impl::ns::BackendContext, \
	orhi::impl::ns::BufferContext, \
	orhi::impl::ns::CommandBufferContext, \
	orhi::impl::ns::CommandPoolContext, \
	orhi::impl::ns::DescriptorContext, \
	orhi::impl::ns::DescriptorPoolContext, \
	orhi::impl::ns::DescriptorSetContext, \
	orhi::impl::ns::DescriptorSetLayoutContext, \
	orhi::impl::ns::DeviceContext, \
	orhi::impl::ns::FenceContext, \
	orhi::impl::ns::FramebufferContext, \
	orhi::impl::ns::GraphicsPipelineContext, \
	orhi::impl::ns::QueueContext, \
	orhi::impl::ns::RenderPassContext, \
	orhi::impl::ns::SemaphoreContext, \
	orhi::impl::ns::ShaderModuleContext, \
	orhi::impl::ns::SwapChainContext, \
	orhi::impl::ns::TextureContext \
>
