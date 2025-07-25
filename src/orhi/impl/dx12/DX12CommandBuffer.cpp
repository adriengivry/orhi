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
		Device& p_device,
		CommandPool& p_commandPool
	) : m_context({ p_device, p_commandPool, nullptr })
	{
		auto device = p_device.GetNativeHandle().As<ID3D12Device*>();
		auto commandAllocator = p_commandPool.GetNativeHandle().As<ID3D12CommandAllocator*>();
		ORHI_ASSERT(commandAllocator, "Command pool must have a valid command allocator");
		ORHI_ASSERT(device, "Device must have a valid native handle");

		HRESULT hr = device->CreateCommandList(
			0, // Node mask
			D3D12_COMMAND_LIST_TYPE_DIRECT, // Command list type
			commandAllocator, // Command allocator
			nullptr, // Initial pipeline state (null for no initial state)
			IID_PPV_ARGS(&m_context.commandList)
		);

		ORHI_ASSERT(SUCCEEDED(hr), "Failed to create command list");

		// Close command list first
		hr = m_context.commandList->Close();
		ORHI_ASSERT(SUCCEEDED(hr), "Failed to close command list");

		// Set native handle to the command list
		m_handle = m_context.commandList.Get();

	}

	template<>
	CommandBuffer::~TCommandBuffer()
	{
	}

	template<>
	void CommandBuffer::Reset()
	{
		
		ORHI_ASSERT(m_context.commandList, "Command list must have a valid native handle");

		HRESULT hr = m_context.commandList->Reset(
			m_context.commandPool.GetNativeHandle().As<ID3D12CommandAllocator*>(),
			nullptr // Initial pipeline state (null for no initial state)
		);
		ORHI_ASSERT(SUCCEEDED(hr), "Failed to reset command list");

	}

	template<>
	void CommandBuffer::Begin(types::ECommandBufferUsageFlags p_flags)
	{
		// In DirectX 12, command lists are implicitly begun when reset
		// The flags don't have direct equivalents in DX12
		// Command recording starts immediately after Reset()
		Reset();

	}

	template<>
	void CommandBuffer::End()
	{
		// Close the command list to finish recording commands
		HRESULT hr = m_context.commandList->Close();
		ORHI_ASSERT(SUCCEEDED(hr), "Failed to close command list");
		// After closing, the command list is ready to be submitted for execution
	}

	template<>
	void CommandBuffer::BeginRenderPass(
		RenderPass& p_renderPass,
		Framebuffer& p_framebuffer,
		math::Extent2D p_extent,
		std::initializer_list<data::ClearValue> p_clearValues
	)
	{
		auto commandList = m_handle.As<ID3D12GraphicsCommandList*>();


		std::vector<D3D12_CLEAR_VALUE> clearValues;
		clearValues.reserve(p_clearValues.size());

		for (const auto& clearValue : p_clearValues)
		{
			if (auto colorClearValue = std::get_if<data::ColorClearValue>(&clearValue); colorClearValue)
			{
				clearValues.push_back(D3D12_CLEAR_VALUE{
					.Color = {
						colorClearValue->x,
						colorClearValue->y,
						colorClearValue->z,
						colorClearValue->w
					}
					});
			}
			else if (auto depthStencilClearValue = std::get_if<data::DepthStencilClearValue>(&clearValue); depthStencilClearValue)
			{
				clearValues.push_back(D3D12_CLEAR_VALUE{
					.DepthStencil = {
						.Depth = depthStencilClearValue->depth,
						.Stencil = static_cast<uint8_t>(depthStencilClearValue->stencil)
					}
					});
			}
			else
			{
				ORHI_ASSERT(false, "Unsupported clear value type");
			}
		}

		// commandList->OMSetRenderTargets();

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
		auto commandList = m_handle.As<ID3D12GraphicsCommandList*>();
		ORHI_ASSERT(commandList, "Command list must have a valid native handle");
		D3D12_INDEX_BUFFER_VIEW indexBufferView;
		indexBufferView.BufferLocation = p_indexBuffer.GetNativeHandle().As<ID3D12Resource*>()->GetGPUVirtualAddress() + p_offset;
		// indexBufferView.SizeInBytes = static_cast<UINT>(p_indexBuffer.GetSize() - p_offset);
		indexBufferView.Format = orhi::utils::EnumToValue<DXGI_FORMAT>(p_indexType);

		commandList->IASetIndexBuffer(&indexBufferView);
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

	// When using vertex buffers in dx12, you go through the vertex buffer view
	template<>
	void CommandBuffer::BindVertexBuffers(
		std::span<const std::reference_wrapper<Buffer>> p_buffers,
		std::span<const uint64_t> p_offsets
	)
	{
		auto commandList = m_handle.As<ID3D12GraphicsCommandList*>();
		ORHI_ASSERT(commandList, "Command list must have a valid native handle");
		// Ensure the number of buffers matches the number of offsets
		ORHI_ASSERT(p_buffers.size() == p_offsets.size(), "Number of buffers must match number of offsets");
		std::vector<ID3D12Resource*> dxBuffers;
		dxBuffers.reserve(p_buffers.size());
		for (const auto& buffer : p_buffers)
		{
			dxBuffers.push_back(buffer.get().GetNativeHandle().As<ID3D12Resource*>());
		}
		std::vector<D3D12_VERTEX_BUFFER_VIEW> vertexBufferViews;
		vertexBufferViews.reserve(p_buffers.size());
		for (size_t i = 0; i < p_buffers.size(); ++i)
		{
			const auto& buffer = p_buffers[i].get();
			D3D12_VERTEX_BUFFER_VIEW vbv = {};
			vbv.BufferLocation = buffer.GetNativeHandle().As<ID3D12Resource*>()->GetGPUVirtualAddress() + p_offsets[i];
			//vbv.SizeInBytes = static_cast<UINT>(buffer.GetSize() - p_offsets[i]);
			//vbv.StrideInBytes = buffer.GetStride();
			vertexBufferViews.push_back(vbv);
		}
		commandList->IASetVertexBuffers(
			0, // Start slot
			static_cast<UINT>(vertexBufferViews.size()), // Number of buffers
			vertexBufferViews.data() // Array of buffers
		);

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
