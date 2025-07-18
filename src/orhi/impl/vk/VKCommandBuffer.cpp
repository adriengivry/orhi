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
#include <orhi/impl/vk/Pipeline.h>
#include <orhi/impl/vk/PipelineLayout.h>
#include <orhi/impl/vk/RenderPass.h>
#include <orhi/impl/vk/Texture.h>
#include <orhi/impl/vk/detail/MemoryUtils.h>
#include <orhi/impl/vk/detail/Types.h>

#include <vulkan/vulkan.h>

using namespace orhi::impl::vk;

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
		vkResetCommandBuffer(
			m_handle.As<VkCommandBuffer>(),
			0
		);
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
			m_handle.As<VkCommandBuffer>(),
			&beginInfo
		);

		ORHI_ASSERT(result == VK_SUCCESS, "failed to begin recording command buffer!");
	}

	template<>
	void CommandBuffer::End()
	{
		VkResult result = vkEndCommandBuffer(m_handle.As<VkCommandBuffer>());
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
			m_handle.As<VkCommandBuffer>(),
			&renderPassInfo,
			VK_SUBPASS_CONTENTS_INLINE
		);
	}

	template<>
	void CommandBuffer::EndRenderPass()
	{
		vkCmdEndRenderPass(m_handle.As<VkCommandBuffer>());
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
			m_handle.As<VkCommandBuffer>(),
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
		types::ETextureLayout p_layout,
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
			m_handle.As<VkCommandBuffer>(),
			p_src.GetNativeHandle().As<VkBuffer>(),
			p_dest.GetNativeHandle().As<VkImage>(),
			utils::EnumToValue<VkImageLayout>(p_layout),
			std::max(1U, static_cast<uint32_t>(p_regions.size())),
			regions.data()
		);
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
		VkImageMemoryBarrier barrier = {
			.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER,
			.srcAccessMask = 0,
			.dstAccessMask = 0,
			.oldLayout = utils::EnumToValue<VkImageLayout>(p_oldLayout),
			.newLayout = utils::EnumToValue<VkImageLayout>(p_newLayout),
			.image = p_texture.GetNativeHandle().As<VkImage>(),
			.subresourceRange = {
				.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
				.baseMipLevel = p_baseMipLevel,
				.levelCount = p_mipLevelCount,
				.baseArrayLayer = 0,
				.layerCount = 1
			}
		};

		VkPipelineStageFlags sourceStage;
		VkPipelineStageFlags destinationStage;

		if (p_oldLayout == types::ETextureLayout::UNDEFINED && p_newLayout == types::ETextureLayout::TRANSFER_DST_OPTIMAL)
		{
			barrier.srcAccessMask = 0;
			barrier.dstAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;

			sourceStage = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
			destinationStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
		}
		else if (p_oldLayout == types::ETextureLayout::UNDEFINED && p_newLayout == types::ETextureLayout::TRANSFER_SRC_OPTIMAL)
		{
			barrier.srcAccessMask = 0;
			barrier.dstAccessMask = VK_ACCESS_TRANSFER_READ_BIT;

			sourceStage = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
			destinationStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
		}
		else if (p_oldLayout == types::ETextureLayout::TRANSFER_DST_OPTIMAL && p_newLayout == types::ETextureLayout::SHADER_READ_ONLY_OPTIMAL)
		{
			barrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
			barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;

			sourceStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
			destinationStage = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
		}
		else if (p_oldLayout == types::ETextureLayout::TRANSFER_SRC_OPTIMAL && p_newLayout == types::ETextureLayout::SHADER_READ_ONLY_OPTIMAL)
		{
			barrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
			barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;

			sourceStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
			destinationStage = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
		}
		else if (p_oldLayout == types::ETextureLayout::TRANSFER_DST_OPTIMAL && p_newLayout == types::ETextureLayout::TRANSFER_SRC_OPTIMAL)
		{
			barrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
			barrier.dstAccessMask = VK_ACCESS_TRANSFER_READ_BIT;

			sourceStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
			destinationStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
		}
		else
		{
			throw std::invalid_argument("unsupported layout transition!");
		}

		vkCmdPipelineBarrier(
			m_handle.As<VkCommandBuffer>(),
			sourceStage, destinationStage,
			0, // No flags
			0, nullptr, // No memory barriers
			0, nullptr, // No buffer barriers
			1, &barrier // Image barrier
		);
	}

	template<>
	void CommandBuffer::BindPipeline(
		types::EPipelineBindPoint p_bindPoint,
		Pipeline& p_pipeline
	)
	{
		vkCmdBindPipeline(
			m_handle.As<VkCommandBuffer>(),
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
			m_handle.As<VkCommandBuffer>(),
			p_indexBuffer.GetNativeHandle().As<VkBuffer>(),
			0,
			utils::EnumToValue<VkIndexType>(p_indexType)
		);
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
		math::Rect3D srcRect = p_srcRegion.rect.value_or(
			math::Rect3D{
				.offset = { 0, 0, 0 },
				.extent = p_src.GetExtent()
			}
		);

		math::Rect3D dstRect = p_destRegion.rect.value_or(
			math::Rect3D{
				.offset = { 0, 0, 0 },
				.extent = p_dest.GetExtent()
			}
		);

		VkImageBlit blitRegion{
			.srcSubresource = {
				.aspectMask = utils::EnumToValue<VkImageAspectFlags>(p_srcRegion.aspectMask),
				.mipLevel = p_srcRegion.mipLevel,
				.baseArrayLayer = p_srcRegion.baseArrayLayer,
				.layerCount = p_srcRegion.layerCount
			},
			.srcOffsets = {
				{ static_cast<int32_t>(srcRect.offset.x), static_cast<int32_t>(srcRect.offset.y), 0 },
				{ static_cast<int32_t>(srcRect.offset.x + srcRect.extent.width),
				  static_cast<int32_t>(srcRect.offset.y + srcRect.extent.height), 1 }
			},
			.dstSubresource = {
				.aspectMask = utils::EnumToValue<VkImageAspectFlags>(p_destRegion.aspectMask),
				.mipLevel = p_destRegion.mipLevel,
				.baseArrayLayer = p_destRegion.baseArrayLayer,
				.layerCount = p_destRegion.layerCount
			},
			.dstOffsets = {
				{ static_cast<int32_t>(dstRect.offset.x), static_cast<int32_t>(dstRect.offset.y), 0 },
				{ static_cast<int32_t>(dstRect.offset.x + dstRect.extent.width),
				  static_cast<int32_t>(dstRect.offset.y + dstRect.extent.height), 1 }
			}
		};

		vkCmdBlitImage(
			m_handle.As<VkCommandBuffer>(),
			p_src.GetNativeHandle().As<VkImage>(),
			utils::EnumToValue<VkImageLayout>(p_srcLayout),
			p_dest.GetNativeHandle().As<VkImage>(),
			utils::EnumToValue<VkImageLayout>(p_destLayout),
			1, &blitRegion,
			VK_FILTER_LINEAR // Use linear filtering for the blit operation
		);
	}

	template<>
	void CommandBuffer::BindVertexBuffers(
		std::span<const std::reference_wrapper<Buffer>> p_buffers,
		std::span<const uint64_t> p_offsets
	)
	{
		std::vector<VkBuffer> buffers = detail::MemoryUtils::PrepareArray<VkBuffer>(p_buffers);

		vkCmdBindVertexBuffers(
			m_handle.As<VkCommandBuffer>(),
			0,
			1,
			buffers.data(),
			p_offsets.data()
		);
	}

	template<>
	void CommandBuffer::BindDescriptorSets(
		std::span<const std::reference_wrapper<DescriptorSet>> p_descriptorSets,
		PipelineLayout& p_pipelineLayout,
		types::EPipelineBindPoint p_bindPoint
	)
	{
		std::vector<VkDescriptorSet> descriptorSets = detail::MemoryUtils::PrepareArray<VkDescriptorSet>(p_descriptorSets);

		vkCmdBindDescriptorSets(
			m_handle.As<VkCommandBuffer>(),
			utils::EnumToValue<VkPipelineBindPoint>(p_bindPoint),
			p_pipelineLayout.GetNativeHandle().As<VkPipelineLayout>(),
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
			m_handle.As<VkCommandBuffer>(),
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
			m_handle.As<VkCommandBuffer>(),
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
			m_handle.As<VkCommandBuffer>(),
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
			m_handle.As<VkCommandBuffer>(),
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
		vkCmdDispatch(
			m_handle.As<VkCommandBuffer>(),
			p_groupCountX,
			p_groupCountY,
			p_groupCountZ
		);
	}
}

template class orhi::api::TCommandBuffer<orhi::impl::vk::BackendTraits>;

#endif // #if defined(ORHI_COMPILE_VULKAN)
