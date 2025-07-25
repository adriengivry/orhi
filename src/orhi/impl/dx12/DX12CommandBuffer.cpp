/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry, Jian Bang Xu
* @licence: MIT
*/

#if defined(ORHI_COMPILE_DX12)

#include <orhi/impl/dx12/CommandBuffer.h>

#include <orhi/debug/Assert.h>
#include <orhi/debug/Log.h>
#include <orhi/impl/dx12/Buffer.h>
#include <orhi/impl/dx12/DescriptorSet.h>
#include <orhi/impl/dx12/Framebuffer.h>
#include <orhi/impl/dx12/Pipeline.h>
#include <orhi/impl/dx12/PipelineLayout.h>
#include <orhi/impl/dx12/RenderPass.h>
#include <orhi/impl/dx12/Texture.h>
#include <orhi/impl/dx12/detail/MemoryUtils.h>
#include <orhi/impl/dx12/detail/Types.h>

#include <d3d12.h>
#include <dxgi1_6.h>

using namespace orhi::impl::dx12;

namespace orhi
{
	template<>
	CommandBuffer::TCommandBuffer(
		impl::common::NativeHandle p_handle
	) : BackendObject{ p_handle }
	{

	}

	template<>
	CommandBuffer::~TCommandBuffer()
	{

	}

	template<>
	void CommandBuffer::Reset()
	{
		
	}

	template<>
	void CommandBuffer::Begin(types::ECommandBufferUsageFlags p_flags)
	{
		// In DirectX 12, command lists are implicitly begun when reset
		// The flags don't have direct equivalents in DX12
		// Command recording starts immediately after Reset()
	}

	template<>
	void CommandBuffer::End()
	{
		
	}

	template<>
	void CommandBuffer::BeginRenderPass(
		RenderPass& p_renderPass,
		Framebuffer& p_framebuffer,
		math::Extent2D p_extent,
		std::initializer_list<data::ClearValue> p_clearValues
	)
	{
		
	}

	template<>
	void CommandBuffer::EndRenderPass()
	{
		// In DirectX 12, there's no explicit "end render pass" - 
		// render passes are implicit based on resource transitions
	}

	template<>
	void CommandBuffer::CopyBuffer(
		Buffer& p_src,
		Buffer& p_dest,
		std::span<const data::BufferCopyDesc> p_regions
	)
	{
	}

	template<>
	void CommandBuffer::CopyBufferToTexture(
		Buffer& p_src,
		Texture& p_dest,
		types::ETextureLayout p_layout,
		std::span<const data::BufferTextureCopyDesc> p_regions
	)
	{
	}

	template<>
	void CommandBuffer::TransitionTextureLayout(
		Texture& p_texture,
		types::ETextureLayout p_oldLayout,
		types::ETextureLayout p_newLayout,
		uint32_t p_baseMipLevel,
		uint32_t p_mipLevelCount
	)
	{
	}

	template<>
	void CommandBuffer::BindPipeline(
		types::EPipelineBindPoint p_bindPoint,
		Pipeline& p_pipeline
	)
	{
	}

	template<>
	void CommandBuffer::BindIndexBuffer(
		const Buffer& p_indexBuffer,
		uint64_t p_offset,
		types::EIndexType p_indexType
	)
	{
	}

	template<>
	void CommandBuffer::BlitTexture(
		Texture& p_src,
		Texture& p_dest,
		const data::TextureRegion& p_srcRegion,
		const data::TextureRegion& p_destRegion,
		types::ETextureLayout p_srcLayout,
		types::ETextureLayout p_destLayout
	)
	{
		// DirectX 12 doesn't have a direct blit operation like Vulkan
		// Maybe use a compute shader to do the blit?
	}

	template<>
	void CommandBuffer::BindVertexBuffers(
		std::span<const std::reference_wrapper<Buffer>> p_buffers,
		std::span<const uint64_t> p_offsets
	)
	{
	}

	template<>
	void CommandBuffer::BindDescriptorSets(
		std::span<const std::reference_wrapper<DescriptorSet>> p_descriptorSets,
		PipelineLayout& p_pipelineLayout,
		types::EPipelineBindPoint p_bindPoint
	)
	{
	}

	template<>
	void CommandBuffer::PushConstants(
		PipelineLayout& p_pipelineLayout,
		types::EShaderStageFlags p_stageFlags,
		const data::MemoryRange& p_range,
		const void* p_data
	)
	{
		// DirectX 12 does not have a direct equivalent to Vulkan's push constants
		// Maybe something similar can be achieved by calling SetGraphicsRoot32BitConstants
	}

	template<>
	void CommandBuffer::SetViewport(
		const data::ViewportDesc& p_viewport
	)
	{
		auto commandList = m_handle.As<ID3D12GraphicsCommandList*>();

		D3D12_VIEWPORT viewport = {};
		viewport.TopLeftX = p_viewport.x;
		viewport.TopLeftY = p_viewport.y;
		viewport.Width = p_viewport.width;
		viewport.Height = p_viewport.height;
		viewport.MinDepth = p_viewport.minDepth;
		viewport.MaxDepth = p_viewport.maxDepth;

		commandList->RSSetViewports(1, &viewport);
	}

	template<>
	void CommandBuffer::SetScissor(
		const math::Rect2D& p_scissor
	)
	{
		auto commandList = m_handle.As<ID3D12GraphicsCommandList*>();

		D3D12_RECT scissorRect = {};
		scissorRect.left = static_cast<LONG>(p_scissor.offset.x);
		scissorRect.top = static_cast<LONG>(p_scissor.offset.y);
		scissorRect.right = static_cast<LONG>(p_scissor.offset.x + p_scissor.extent.width);
		scissorRect.bottom = static_cast<LONG>(p_scissor.offset.y + p_scissor.extent.height);

		commandList->RSSetScissorRects(1, &scissorRect);
	}

	template<>
	void CommandBuffer::Draw(
		uint32_t p_vertexCount,
		uint32_t p_instanceCount
	)
	{
		auto commandList = m_handle.As<ID3D12GraphicsCommandList*>();

		commandList->DrawInstanced(
			p_vertexCount,
			p_instanceCount,
			0,0
		);
	}

	template<>
	void CommandBuffer::DrawIndexed(
		uint32_t p_indexCount,
		uint32_t p_instanceCount
	)
	{
		auto commandList = m_handle.As<ID3D12GraphicsCommandList*>();

		commandList->DrawIndexedInstanced(
			p_indexCount,
			p_instanceCount,
			0, 0, 0
		);
	}

	template<>
	void CommandBuffer::Dispatch(
		uint32_t p_groupCountX,
		uint32_t p_groupCountY,
		uint32_t p_groupCountZ
	)
	{
		auto commandList = m_handle.As<ID3D12GraphicsCommandList*>();

		commandList->Dispatch(
			p_groupCountX,
			p_groupCountY,
			p_groupCountZ
		);
	}
}

template class orhi::api::TCommandBuffer<orhi::impl::dx12::BackendTraits>;

#endif // #if defined(ORHI_COMPILE_DX12)
