/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#if defined(ORHI_COMPILE_VULKAN)

#include <orhi/impl/vk/CommandBuffer.h>

#include <orhi/debug/Assert.h>
#include <orhi/debug/Log.h>
#include <orhi/impl/vk/Buffer.h>
#include <orhi/impl/vk/DescriptorSet.h>
#include <orhi/impl/vk/Framebuffer.h>
#include <orhi/impl/vk/GraphicsPipeline.h>
#include <orhi/impl/vk/RenderPass.h>
#include <orhi/impl/vk/Texture.h>
#include <orhi/impl/vk/details/MemoryUtils.h>
#include <orhi/impl/vk/details/Types.h>

#include <vulkan/vulkan.h>

using namespace orhi::impl::vk;

namespace orhi
{
	template<>
	CommandBuffer::TCommandBuffer(
		data::NativeHandle p_handle
	) : m_context{
		.handle = p_handle.As<VkCommandBuffer>()
	}
	{

	}

	template<>
	CommandBuffer::~TCommandBuffer()
	{

	}

	template<>
	void CommandBuffer::Reset()
	{
		vkResetCommandBuffer(m_context.handle, 0);
	}

	template<>
	void CommandBuffer::Begin(types::ECommandBufferUsageFlags p_flags)
	{
		VkCommandBufferBeginInfo beginInfo{
			.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
			.flags = utils::EnumToValue<VkCommandBufferUsageFlags>(p_flags),
			.pInheritanceInfo = nullptr // Optional
		};

		VkResult result = vkBeginCommandBuffer(
			m_context.handle,
			&beginInfo
		);

		ORHI_ASSERT(result == VK_SUCCESS, "failed to begin recording command buffer!");
	}

	template<>
	void CommandBuffer::End()
	{
		VkResult result = vkEndCommandBuffer(m_context.handle);
		ORHI_ASSERT(result == VK_SUCCESS, "failed to record command buffer!");
	}

	template<>
	void CommandBuffer::BeginRenderPass(
		RenderPass& p_renderPass,
		Framebuffer& p_framebuffer,
		math::Extent2D p_extent,
		std::initializer_list<data::ClearValue> p_clearValues
	)
	{
		std::vector<VkClearValue> clearValues;
		clearValues.reserve(p_clearValues.size());

		for (const auto& clearValue : p_clearValues)
		{
			if (auto colorClearValue = std::get_if<data::ColorClearValue>(&clearValue); colorClearValue)
			{
				clearValues.push_back(VkClearValue{
					.color = {
						colorClearValue->x,
						colorClearValue->y,
						colorClearValue->z,
						colorClearValue->w
					}
				});
			}
			else if (auto depthStencilClearValue = std::get_if<data::DepthStencilClearValue>(&clearValue); depthStencilClearValue)
			{
				clearValues.push_back(VkClearValue{
					.depthStencil = {
						.depth = depthStencilClearValue->depth,
						.stencil = depthStencilClearValue->stencil
					}
				});
			}
			else
			{
				ORHI_ASSERT(false, "Unsupported clear value type");
			}
		}

		VkRenderPassBeginInfo renderPassInfo{
			.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO,
			.renderPass = p_renderPass.GetNativeHandle().As<VkRenderPass>(),
			.framebuffer = p_framebuffer.GetNativeHandle().As<VkFramebuffer>(),
			.renderArea = {
				.offset = { 0, 0 },
				.extent = reinterpret_cast<VkExtent2D&>(p_extent)
			},
			.clearValueCount = static_cast<uint32_t>(clearValues.size()),
			.pClearValues = clearValues.data()
		};

		vkCmdBeginRenderPass(
			m_context.handle,
			&renderPassInfo,
			VK_SUBPASS_CONTENTS_INLINE
		);
	}

	template<>
	void CommandBuffer::EndRenderPass()
	{
		vkCmdEndRenderPass(m_context.handle);
	}

	template<>
	void CommandBuffer::CopyBuffer(
		Buffer& p_src,
		Buffer& p_dest,
		std::span<const data::BufferCopyDesc> p_regions
	)
	{
		std::vector<VkBufferCopy> regions;

		for (const auto& copyDesc : p_regions)
		{
			regions.push_back(VkBufferCopy{
				.srcOffset = copyDesc.srcOffset,
				.dstOffset = copyDesc.dstOffset,
				.size = copyDesc.size,
			});
		}

		if (regions.empty())
		{
			regions.push_back(VkBufferCopy{
				.size = std::min(p_src.GetAllocatedBytes(), p_dest.GetAllocatedBytes())
			});
		}

		vkCmdCopyBuffer(
			m_context.handle,
			p_src.GetNativeHandle().As<VkBuffer>(),
			p_dest.GetNativeHandle().As<VkBuffer>(),
			std::max(1U, static_cast<uint32_t>(p_regions.size())),
			regions.data()
		);
	}

	template<>
	void CommandBuffer::CopyBufferToTexture(
		Buffer& p_src,
		Texture& p_dest,
		std::span<const data::BufferTextureCopyDesc> p_regions
	)
	{
		std::vector<VkBufferImageCopy> regions;

		for (const auto& copyDesc : p_regions)
		{
			regions.push_back(VkBufferImageCopy{
				.bufferOffset = copyDesc.bufferOffset,
				.bufferRowLength = copyDesc.bufferRowLength,
				.bufferImageHeight = copyDesc.bufferImageHeight,
				.imageSubresource = {
					.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
					.mipLevel = 0,
					.baseArrayLayer = 0,
					.layerCount = 1
				},
				.imageOffset = reinterpret_cast<const VkOffset3D&>(copyDesc.imageRect.offset),
				.imageExtent = reinterpret_cast<const VkExtent3D&>(copyDesc.imageRect.extent)
				}
			);
		}

		if (regions.empty())
		{
			regions.push_back(VkBufferImageCopy{
				.bufferOffset = 0,
				.bufferRowLength = 0,
				.bufferImageHeight = 0,
				.imageSubresource = {
					.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
					.mipLevel = 0,
					.baseArrayLayer = 0,
					.layerCount = 1
				},
				.imageOffset = { 0, 0, 0 },
				.imageExtent = reinterpret_cast<const VkExtent3D&>(p_dest.GetExtent())
			});
		}

		vkCmdCopyBufferToImage(
			m_context.handle,
			p_src.GetNativeHandle().As<VkBuffer>(),
			p_dest.GetNativeHandle().As<VkImage>(),
			utils::EnumToValue<VkImageLayout>(p_dest.GetLayout()),
			std::max(1U, static_cast<uint32_t>(p_regions.size())),
			regions.data()
		);
	}

	template<>
	void CommandBuffer::TransitionTextureLayout(
		Texture& p_texture,
		types::ETextureLayout p_layout
	)
	{
		types::ETextureLayout oldLayout = p_texture.GetLayout();

		VkImageMemoryBarrier barrier = {
			.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER,
			.srcAccessMask = 0,
			.dstAccessMask = 0,
			.oldLayout = utils::EnumToValue<VkImageLayout>(oldLayout),
			.newLayout = utils::EnumToValue<VkImageLayout>(p_layout),
			.image = p_texture.GetNativeHandle().As<VkImage>(),
			.subresourceRange = {
				.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
				.baseMipLevel = 0,
				.levelCount = 1,
				.baseArrayLayer = 0,
				.layerCount = 1
			}
		};

		VkPipelineStageFlags sourceStage;
		VkPipelineStageFlags destinationStage;

		if (oldLayout == types::ETextureLayout::UNDEFINED && p_layout == types::ETextureLayout::TRANSFER_DST_OPTIMAL)
		{
			barrier.srcAccessMask = 0;
			barrier.dstAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;

			sourceStage = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
			destinationStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
		}
		else if (oldLayout == types::ETextureLayout::TRANSFER_DST_OPTIMAL && p_layout == types::ETextureLayout::SHADER_READ_ONLY_OPTIMAL)
		{
			barrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
			barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;

			sourceStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
			destinationStage = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
		}
		else
		{
			throw std::invalid_argument("unsupported layout transition!");
		}

		vkCmdPipelineBarrier(
			m_context.handle,
			sourceStage, destinationStage,
			0, // No flags
			0, nullptr, // No memory barriers
			0, nullptr, // No buffer barriers
			1, &barrier // Image barrier
		);

		p_texture.NotifyLayoutChange(p_layout);
	}

	template<>
	void CommandBuffer::BindPipeline(
		types::EPipelineBindPoint p_bindPoint,
		GraphicsPipeline& p_pipeline
	)
	{
		vkCmdBindPipeline(
			m_context.handle,
			utils::EnumToValue<VkPipelineBindPoint>(p_bindPoint),
			p_pipeline.GetNativeHandle().As<VkPipeline>()
		);
	}

	template<>
	void CommandBuffer::BindIndexBuffer(
		const Buffer& p_indexBuffer,
		uint64_t p_offset,
		types::EIndexType p_indexType
	)
	{
		vkCmdBindIndexBuffer(
			m_context.handle,
			p_indexBuffer.GetNativeHandle().As<VkBuffer>(),
			0,
			utils::EnumToValue<VkIndexType>(p_indexType)
		);
	}

	template<>
	void CommandBuffer::BindVertexBuffers(
		std::span<const std::reference_wrapper<Buffer>> p_buffers,
		std::span<const uint64_t> p_offsets
	)
	{
		std::vector<VkBuffer> buffers = details::MemoryUtils::PrepareArray<VkBuffer>(p_buffers);

		vkCmdBindVertexBuffers(
			m_context.handle,
			0,
			1,
			buffers.data(),
			p_offsets.data()
		);
	}

	template<>
	void CommandBuffer::BindDescriptorSets(
		std::span<const std::reference_wrapper<DescriptorSet>> p_descriptorSets,
		data::NativeHandle p_pipelineLayout
	)
	{
		std::vector<VkDescriptorSet> descriptorSets = details::MemoryUtils::PrepareArray<VkDescriptorSet>(p_descriptorSets);

		vkCmdBindDescriptorSets(
			m_context.handle,
			VK_PIPELINE_BIND_POINT_GRAPHICS,
			p_pipelineLayout.As<VkPipelineLayout>(),
			0,
			static_cast<uint32_t>(descriptorSets.size()),
			descriptorSets.data(),
			0,
			nullptr
		);
	}

	template<>
	void CommandBuffer::SetViewport(
		const data::ViewportDesc& p_viewport
	)
	{
		VkViewport viewport{
			.x = p_viewport.x,
			.y = p_viewport.y,
			.width = p_viewport.width,
			.height = p_viewport.height,
			.minDepth = p_viewport.minDepth,
			.maxDepth = p_viewport.maxDepth
		};

		vkCmdSetViewport(
			m_context.handle,
			0, 1,
			&viewport
		);
	}

	template<>
	void CommandBuffer::SetScissor(
		const math::Rect2D& p_scissor
	)
	{
		VkRect2D scissor = reinterpret_cast<const VkRect2D&>(p_scissor);

		vkCmdSetScissor(
			m_context.handle,
			0, 1,
			&scissor
		);
	}

	template<>
	void CommandBuffer::Draw(
		uint32_t p_vertexCount,
		uint32_t p_instanceCount
	)
	{
		vkCmdDraw(
			m_context.handle,
			p_vertexCount,
			p_instanceCount,
			0, 0
		);
	}

	template<>
	void CommandBuffer::DrawIndexed(
		uint32_t p_indexCount,
		uint32_t p_instanceCount
	)
	{
		vkCmdDrawIndexed(
			m_context.handle,
			p_indexCount,
			p_instanceCount,
			0, 0, 0
		);
	}

	template<>
	data::NativeHandle CommandBuffer::GetNativeHandle() const
	{
		return m_context.handle;
	}
}

template class orhi::api::TCommandBuffer<orhi::impl::vk::BackendTraits>;

#endif // #if defined(ORHI_COMPILE_VULKAN)
