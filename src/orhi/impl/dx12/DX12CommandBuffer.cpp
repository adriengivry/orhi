/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry, Jian Bang Xu, Robert Osborne
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

		// Command allocators must be reset before resetting the command list as well

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

	template <>
	void CommandBuffer::BeginRendering(const RenderingInfo<BackendTraits>& p_info)
	{
		auto commandList = m_context.commandList.As<ID3D12GraphicsCommandList*>();
		ORHI_ASSERT(commandList, "Command list must have a valid native handle");

		D3D12_CPU_DESCRIPTOR_HANDLE rtvHandles[8] = {};

		for (uint32_t i = 0; i < p_info.numRenderTargets; ++i)
		{
			auto framebuffer = p_info.framebuffer[i];
			ORHI_ASSERT(framebuffer, "Framebuffer must not be null");

			// Set render targets and clear values
			// TODO: Need to get native render target views from framebuffer
			Framebuffer& fb = p_info.framebuffer[i]->GetNativeHandle().As<Framebuffer&>();
			float clearColor[4] = { p_info.clearColor[i].x,
								 p_info.clearColor[i].y,
								 p_info.clearColor[i].z,
								 p_info.clearColor[i].w };
			rtvHandles[i] = fb->GetNativeHandle().As<D3D12_CPU_DESCRIPTOR_HANDLE>()->GetRenderTargetView();
			commandList->ClearRenderTargetView(rtvHandles[i], clearColor, 0, nullptr);
		}

		// TODO: Handle depth attachments if present 

		commandList->OMSetRenderTargets(
			p_info.numRenderTargets,
			rtvHandles,
			FALSE, // No need to preserve old render targets
			nullptr // No depth stencil view for now
		);

		D3D12_VIEWPORT viewport = {};
		viewport.TopLeftX = p_info.viewport.x;
		viewport.TopLeftY = p_info.viewport.y;
		viewport.Width = p_info.viewport.width;
		viewport.Height = p_info.viewport.height;
		viewport.MinDepth = p_info.viewport.minDepth;
		viewport.MaxDepth = p_info.viewport.maxDepth;
		commandList->RSSetViewports(1, &viewport);

		D3D12_RECT scissorRect = {};
		scissorRect.left = p_info.viewport.x;
		scissorRect.top = p_info.viewport.y;
		scissorRect.right = p_info.viewport.x + p_info.viewport.width;
		scissorRect.bottom = p_info.viewport.y + p_info.viewport.height;
		commandList->RSSetScissorRects(1, &scissorRect);
	}

	template <>
	void CommandBuffer::EndRendering()
	{
		auto commandList = m_context.commandList.As<ID3D12GraphicsCommandList*>();
		ORHI_ASSERT(commandList, "Command list must have a valid native handle");
		// In DirectX 12, there's no explicit "end rendering" - 
		// rendering is implicit based on resource transitions
		// No action needed here

		// Reset render targets to null
		commandList->OMSetRenderTargets(
			0, // No render targets
			nullptr, // No render target views
			FALSE,
			nullptr // No depth stencil view
		);

	}

	template<>
	void CommandBuffer::BeginRenderPass(
		RenderPass& p_renderPass,
		Framebuffer& p_framebuffer,
		math::Extent2D p_extent,
		std::initializer_list<data::ClearValue> p_clearValues
	)
	{
		// TODO: subject for removal
		// auto commandList = m_handle.As<ID3D12GraphicsCommandList*>();
		// ORHI_ASSERT(commandList, "Command list must have a valid native handle");

		// // Get render target and depth stencil views from framebuffer
		
		// // The set render targets function needs to have access to the CPU descriptor handles
		// // The heap holding these descriptors needs to be stored somewhere
		
		// // TODO: Get actual render target views and depth stencil view from framebuffer
		// std::vector<D3D12_CPU_DESCRIPTOR_HANDLE> rtvHandles;
		// D3D12_CPU_DESCRIPTOR_HANDLE dsvHandle = {};
		// bool hasDSV = false;

		// // Set render targets (placeholder - needs actual framebuffer implementation)
		// if (!rtvHandles.empty() || hasDSV)
		// {
		// 	commandList->OMSetRenderTargets(
		// 		static_cast<UINT>(rtvHandles.size()),
		// 		rtvHandles.empty() ? nullptr : rtvHandles.data(),
		// 		FALSE,
		// 		hasDSV ? &dsvHandle : nullptr
		// 	);
		// }

		// // Clear render targets and depth stencil
		// size_t clearIndex = 0;
		// for (const auto& clearValue : p_clearValues)
		// {
		// 	if (auto colorClearValue = std::get_if<data::ColorClearValue>(&clearValue); colorClearValue)
		// 	{
		// 		if (clearIndex < rtvHandles.size())
		// 		{
		// 			FLOAT clearColor[4] = {
		// 				colorClearValue->x,
		// 				colorClearValue->y,
		// 				colorClearValue->z,
		// 				colorClearValue->w
		// 			};
		// 			commandList->ClearRenderTargetView(rtvHandles[clearIndex], clearColor, 0, nullptr);
		// 		}
		// 	}
		// 	else if (auto depthStencilClearValue = std::get_if<data::DepthStencilClearValue>(&clearValue); depthStencilClearValue)
		// 	{
		// 		if (hasDSV)
		// 		{
		// 			commandList->ClearDepthStencilView(
		// 				dsvHandle,
		// 				D3D12_CLEAR_FLAG_DEPTH | D3D12_CLEAR_FLAG_STENCIL,
		// 				depthStencilClearValue->depth,
		// 				static_cast<UINT8>(depthStencilClearValue->stencil),
		// 				0,
		// 				nullptr
		// 			);
		// 		}
		// 	}
		// 	clearIndex++;
		// }
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
		auto commandList = m_handle.As<ID3D12GraphicsCommandList*>();
		ORHI_ASSERT(commandList, "Command list must have a valid native handle");

		auto srcResource = p_src.GetNativeHandle().As<ID3D12Resource*>();
		auto destResource = p_dest.GetNativeHandle().As<ID3D12Resource*>();
		ORHI_ASSERT(srcResource, "Source buffer must have a valid native handle");
		ORHI_ASSERT(destResource, "Destination buffer must have a valid native handle");

		for (const auto& region : p_regions)
		{
			//commandList->CopyBufferRegion(
			//	destResource,
			//	// TODO: Need to handle offset properly
			//	region.destOffset,
			//	srcResource,
			//	region.srcOffset,
			//	region.size
			//);
		}
	}

	template<>
	void CommandBuffer::CopyBufferToTexture(
		Buffer& p_src,
		Texture& p_dest,
		types::ETextureLayout p_layout,
		std::span<const data::BufferTextureCopyDesc> p_regions
	)
	{
		auto commandList = m_handle.As<ID3D12GraphicsCommandList*>();
		ORHI_ASSERT(commandList, "Command list must have a valid native handle");

		auto srcResource = p_src.GetNativeHandle().As<ID3D12Resource*>();
		auto destResource = p_dest.GetNativeHandle().As<ID3D12Resource*>();
		ORHI_ASSERT(srcResource, "Source buffer must have a valid native handle");
		ORHI_ASSERT(destResource, "Destination texture must have a valid native handle");
		// TODO: Need to add members, doesn't currently compile
		for (const auto& region : p_regions)
		{
			//D3D12_TEXTURE_COPY_LOCATION srcLocation = {};
			//srcLocation.pResource = srcResource;
			//srcLocation.Type = D3D12_TEXTURE_COPY_TYPE_PLACED_FOOTPRINT;
			//srcLocation.PlacedFootprint.Offset = region.bufferOffset;
			//srcLocation.PlacedFootprint.Footprint.Format = destResource->GetDesc().Format;
			//srcLocation.PlacedFootprint.Footprint.Width = region.textureExtent.width;
			//srcLocation.PlacedFootprint.Footprint.Height = region.textureExtent.height;
			//srcLocation.PlacedFootprint.Footprint.Depth = region.textureExtent.depth;
			//srcLocation.PlacedFootprint.Footprint.RowPitch = region.bufferRowLength * 4; // Assuming 4 bytes per pixel, this should be calculated properly

			//D3D12_TEXTURE_COPY_LOCATION destLocation = {};
			//destLocation.pResource = destResource;
			//destLocation.Type = D3D12_TEXTURE_COPY_TYPE_SUBRESOURCE_INDEX;
			//destLocation.SubresourceIndex = region.textureSubresource.mipLevel + 
			//	(region.textureSubresource.arrayLayer * destResource->GetDesc().MipLevels);

			//D3D12_BOX srcBox = {};
			//srcBox.left = 0;
			//srcBox.top = 0;
			//srcBox.front = 0;
			//srcBox.right = region.textureExtent.width;
			//srcBox.bottom = region.textureExtent.height;
			//srcBox.back = region.textureExtent.depth;

			//commandList->CopyTextureRegion(
			//	&destLocation,
			//	region.textureOffset.x,
			//	region.textureOffset.y,
			//	region.textureOffset.z,
			//	&srcLocation,
			//	&srcBox
			//);
		}
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
		auto commandList = m_handle.As<ID3D12GraphicsCommandList*>();
		ORHI_ASSERT(commandList, "Command list must have a valid native handle");

		auto resource = p_texture.GetNativeHandle().As<ID3D12Resource*>();
		ORHI_ASSERT(resource, "Texture must have a valid native handle");

		// Convert ORHI texture layouts to D3D12 resource states
		// TODO: Extract out into a free function later


		D3D12_RESOURCE_STATES beforeState = ConvertTextureLayoutToResourceState(p_oldLayout);
		D3D12_RESOURCE_STATES afterState = ConvertTextureLayoutToResourceState(p_newLayout);

		// Only create barrier if states are different
		if (beforeState != afterState)
		{
			D3D12_RESOURCE_BARRIER barrier = {};
			barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
			barrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
			barrier.Transition.pResource = resource;
			barrier.Transition.StateBefore = beforeState;
			barrier.Transition.StateAfter = afterState;
			barrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;

			// If specific mip levels are specified, handle them individually
			if (p_mipLevelCount != UINT32_MAX && p_mipLevelCount > 0)
			{
				for (uint32_t mip = p_baseMipLevel; mip < p_baseMipLevel + p_mipLevelCount; ++mip)
				{
					barrier.Transition.Subresource = mip;
					commandList->ResourceBarrier(1, &barrier);
				}
			}
			else
			{
				commandList->ResourceBarrier(1, &barrier);
			}
		}
	}

	template<>
	void CommandBuffer::BindPipeline(
		types::EPipelineBindPoint p_bindPoint,
		Pipeline& p_pipeline
	)
	{
		// TODO: This is only a placeholder implementation
		auto commandList = m_handle.As<ID3D12GraphicsCommandList*>();
		ORHI_ASSERT(commandList, "Command list must have a valid native handle");

		auto pipelineState = p_pipeline.GetNativeHandle().As<ID3D12PipelineState*>();
		ORHI_ASSERT(pipelineState, "Pipeline must have a valid pipeline state");

		// Set the pipeline state
		commandList->SetPipelineState(pipelineState);

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
		// TODO: Need a way to get the size of the buffer from the buffer itself
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

			// TODO: Need a way to get the size and stride of the buffer from the buffer itself
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
		auto commandList = m_handle.As<ID3D12GraphicsCommandList*>();
		ORHI_ASSERT(commandList, "Command list must have a valid native handle");

		auto rootSignature = p_pipelineLayout.GetNativeHandle().As<ID3D12RootSignature*>();
		ORHI_ASSERT(rootSignature, "Pipeline layout must have a valid root signature");

		// Set the root signature based on bind point
		if (p_bindPoint == types::EPipelineBindPoint::GRAPHICS)
		{
			commandList->SetGraphicsRootSignature(rootSignature);
		}
		else if (p_bindPoint == types::EPipelineBindPoint::COMPUTE)
		{
			commandList->SetComputeRootSignature(rootSignature);
		}

		// Set descriptor heaps
		std::vector<ID3D12DescriptorHeap*> descriptorHeaps;
		descriptorHeaps.reserve(p_descriptorSets.size());
		
		for (const auto& descriptorSet : p_descriptorSets)
		{
			auto heap = descriptorSet.get().GetNativeHandle().As<ID3D12DescriptorHeap*>();
			if (heap)
			{
				descriptorHeaps.push_back(heap);
			}
		}

		if (!descriptorHeaps.empty())
		{
			commandList->SetDescriptorHeaps(static_cast<UINT>(descriptorHeaps.size()), descriptorHeaps.data());

			// Bind descriptor tables to root signature
			// TODO: Need to handle heap indices properly
			for (size_t i = 0; i < p_descriptorSets.size(); ++i)
			{
				auto heap = descriptorHeaps[i];
				D3D12_GPU_DESCRIPTOR_HANDLE gpuHandle = heap->GetGPUDescriptorHandleForHeapStart();

				if (p_bindPoint == types::EPipelineBindPoint::GRAPHICS)
				{
					commandList->SetGraphicsRootDescriptorTable(static_cast<UINT>(i), gpuHandle);
				}
				else if (p_bindPoint == types::EPipelineBindPoint::COMPUTE)
				{
					commandList->SetComputeRootDescriptorTable(static_cast<UINT>(i), gpuHandle);
				}
			}
		}
	}

	template<>
	void CommandBuffer::PushConstants(
		PipelineLayout& p_pipelineLayout,
		types::EShaderStageFlags p_stageFlags,
		const data::MemoryRange& p_range,
		const void* p_data
	)
	{
		auto commandList = m_handle.As<ID3D12GraphicsCommandList*>();
		ORHI_ASSERT(commandList, "Command list must have a valid native handle");

		// DirectX 12 doesn't have push constants like Vulkan, but we can use root constants
		// This is a simplified implementation that assumes the push constants are mapped to root parameter 0
		
		ORHI_ASSERT(p_range.size % 4 == 0, "Push constant size must be a multiple of 4 bytes");
		ORHI_ASSERT(p_range.offset % 4 == 0, "Push constant offset must be a multiple of 4 bytes");
		
		uint32_t num32BitValues = static_cast<uint32_t>(p_range.size / 4);
		uint32_t destOffsetIn32BitValues = static_cast<uint32_t>(p_range.offset / 4);
		
		// Determine if this is for graphics or compute pipeline based on stage flags
		bool isGraphics = (p_stageFlags & (types::EShaderStageFlags::VERTEX_BIT | 
										   types::EShaderStageFlags::FRAGMENT_BIT | 
										   types::EShaderStageFlags::GEOMETRY_BIT | 
										   types::EShaderStageFlags::TESSELLATION_CONTROL_BIT | 
										   types::EShaderStageFlags::TESSELLATION_EVALUATION_BIT)) != types::EShaderStageFlags::NONE;
		
		bool isCompute = (p_stageFlags & types::EShaderStageFlags::COMPUTE_BIT) != types::EShaderStageFlags::NONE;
		
		// this would need to be determined from the pipeline layout
		const UINT rootParameterIndex = 0;
		
		if (isGraphics)
		{
			commandList->SetGraphicsRoot32BitConstants(
				rootParameterIndex,
				num32BitValues,
				p_data,
				destOffsetIn32BitValues
			);
		}
		
		if (isCompute)
		{
			commandList->SetComputeRoot32BitConstants(
				rootParameterIndex,
				num32BitValues,
				p_data,
				destOffsetIn32BitValues
			);
		}
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
