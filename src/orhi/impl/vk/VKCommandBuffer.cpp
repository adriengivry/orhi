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
#include <orhi/impl/vk/Texture.h>
#include <orhi/impl/vk/detail/MemoryUtils.h>
#include <orhi/impl/vk/detail/Types.h>

#include <vulkan/vulkan.h>

#include <algorithm>
#include <stdexcept>

using namespace orhi::impl::vk;

namespace
{
	struct LayoutAccess
	{
		VkPipelineStageFlags stage;
		VkAccessFlags access;
	};

	LayoutAccess GetLayoutAccess(orhi::types::ETextureLayout p_layout)
	{
		switch (p_layout)
		{
		case orhi::types::ETextureLayout::UNDEFINED:
			return { VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT, 0 };
		case orhi::types::ETextureLayout::COLOR_ATTACHMENT_OPTIMAL:
			return {
				VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
				VK_ACCESS_COLOR_ATTACHMENT_READ_BIT | VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT
			};
		case orhi::types::ETextureLayout::DEPTH_STENCIL_ATTACHMENT_OPTIMAL:
			return {
				VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT | VK_PIPELINE_STAGE_LATE_FRAGMENT_TESTS_BIT,
				VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_READ_BIT | VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT
			};
		case orhi::types::ETextureLayout::DEPTH_STENCIL_READ_ONLY_OPTIMAL:
		case orhi::types::ETextureLayout::DEPTH_READ_ONLY_OPTIMAL:
		case orhi::types::ETextureLayout::STENCIL_READ_ONLY_OPTIMAL:
		case orhi::types::ETextureLayout::SHADER_READ_ONLY_OPTIMAL:
			return { VK_PIPELINE_STAGE_ALL_COMMANDS_BIT, VK_ACCESS_MEMORY_READ_BIT };
		case orhi::types::ETextureLayout::DEPTH_READ_ONLY_STENCIL_ATTACHMENT_OPTIMAL:
		case orhi::types::ETextureLayout::DEPTH_ATTACHMENT_STENCIL_READ_ONLY_OPTIMAL:
		case orhi::types::ETextureLayout::DEPTH_ATTACHMENT_OPTIMAL:
		case orhi::types::ETextureLayout::STENCIL_ATTACHMENT_OPTIMAL:
			return {
				VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT | VK_PIPELINE_STAGE_LATE_FRAGMENT_TESTS_BIT,
				VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_READ_BIT | VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT
			};
		case orhi::types::ETextureLayout::ATTACHMENT_OPTIMAL:
			return {
				VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT |
					VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT |
					VK_PIPELINE_STAGE_LATE_FRAGMENT_TESTS_BIT,
				VK_ACCESS_COLOR_ATTACHMENT_READ_BIT |
					VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT |
					VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_READ_BIT |
					VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT
			};
		case orhi::types::ETextureLayout::READ_ONLY_OPTIMAL:
			return { VK_PIPELINE_STAGE_ALL_COMMANDS_BIT, VK_ACCESS_MEMORY_READ_BIT };
		case orhi::types::ETextureLayout::GENERAL:
			return {
				VK_PIPELINE_STAGE_ALL_COMMANDS_BIT,
				VK_ACCESS_MEMORY_READ_BIT | VK_ACCESS_MEMORY_WRITE_BIT
			};
		case orhi::types::ETextureLayout::TRANSFER_SRC_OPTIMAL:
			return { VK_PIPELINE_STAGE_TRANSFER_BIT, VK_ACCESS_TRANSFER_READ_BIT };
		case orhi::types::ETextureLayout::TRANSFER_DST_OPTIMAL:
			return { VK_PIPELINE_STAGE_TRANSFER_BIT, VK_ACCESS_TRANSFER_WRITE_BIT };
		case orhi::types::ETextureLayout::PREINITIALIZED:
			return { VK_PIPELINE_STAGE_HOST_BIT, VK_ACCESS_HOST_WRITE_BIT };
		case orhi::types::ETextureLayout::PRESENT_SRC_KHR:
			return { VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT, 0 };
		default:
			throw std::invalid_argument("unsupported rendering attachment layout");
		}
	}

	VkResolveModeFlagBits GetColorResolveMode(orhi::types::EFormat p_format)
	{
		switch (p_format)
		{
		case orhi::types::EFormat::R8_UINT:
		case orhi::types::EFormat::R8_SINT:
		case orhi::types::EFormat::R8G8_UINT:
		case orhi::types::EFormat::R8G8_SINT:
		case orhi::types::EFormat::R8G8B8_UINT:
		case orhi::types::EFormat::R8G8B8_SINT:
		case orhi::types::EFormat::B8G8R8_UINT:
		case orhi::types::EFormat::B8G8R8_SINT:
		case orhi::types::EFormat::R8G8B8A8_UINT:
		case orhi::types::EFormat::R8G8B8A8_SINT:
		case orhi::types::EFormat::B8G8R8A8_UINT:
		case orhi::types::EFormat::B8G8R8A8_SINT:
		case orhi::types::EFormat::A8B8G8R8_UINT_PACK32:
		case orhi::types::EFormat::A8B8G8R8_SINT_PACK32:
		case orhi::types::EFormat::A2R10G10B10_UINT_PACK32:
		case orhi::types::EFormat::A2R10G10B10_SINT_PACK32:
		case orhi::types::EFormat::A2B10G10R10_UINT_PACK32:
		case orhi::types::EFormat::A2B10G10R10_SINT_PACK32:
		case orhi::types::EFormat::R16_UINT:
		case orhi::types::EFormat::R16_SINT:
		case orhi::types::EFormat::R16G16_UINT:
		case orhi::types::EFormat::R16G16_SINT:
		case orhi::types::EFormat::R16G16B16_UINT:
		case orhi::types::EFormat::R16G16B16_SINT:
		case orhi::types::EFormat::R16G16B16A16_UINT:
		case orhi::types::EFormat::R16G16B16A16_SINT:
		case orhi::types::EFormat::R32_UINT:
		case orhi::types::EFormat::R32_SINT:
		case orhi::types::EFormat::R32G32_UINT:
		case orhi::types::EFormat::R32G32_SINT:
		case orhi::types::EFormat::R32G32B32_UINT:
		case orhi::types::EFormat::R32G32B32_SINT:
		case orhi::types::EFormat::R32G32B32A32_UINT:
		case orhi::types::EFormat::R32G32B32A32_SINT:
		case orhi::types::EFormat::R64_UINT:
		case orhi::types::EFormat::R64_SINT:
		case orhi::types::EFormat::R64G64_UINT:
		case orhi::types::EFormat::R64G64_SINT:
		case orhi::types::EFormat::R64G64B64_UINT:
		case orhi::types::EFormat::R64G64B64_SINT:
		case orhi::types::EFormat::R64G64B64A64_UINT:
		case orhi::types::EFormat::R64G64B64A64_SINT:
			return VK_RESOLVE_MODE_SAMPLE_ZERO_BIT;
		default:
			return VK_RESOLVE_MODE_AVERAGE_BIT;
		}
	}

	orhi::types::ETextureLayout GetAttachmentLayout(orhi::types::EAttachmentType p_type)
	{
		return p_type == orhi::types::EAttachmentType::DEPTH_STENCIL
			? orhi::types::ETextureLayout::DEPTH_STENCIL_ATTACHMENT_OPTIMAL
			: orhi::types::ETextureLayout::COLOR_ATTACHMENT_OPTIMAL;
	}

	void TransitionAttachment(
		VkCommandBuffer p_commandBuffer,
		const orhi::impl::vk::FramebufferAttachment& p_attachment,
		orhi::types::ETextureLayout p_oldLayout,
		orhi::types::ETextureLayout p_newLayout
	)
	{
		auto source = GetLayoutAccess(p_oldLayout);
		const auto destination = GetLayoutAccess(p_newLayout);
		// Order discard transitions after prior attachment writes and swapchain acquisition waits.
		if (p_oldLayout == orhi::types::ETextureLayout::UNDEFINED)
		{
			source = destination;
		}
		else if (p_oldLayout == orhi::types::ETextureLayout::PRESENT_SRC_KHR)
		{
			source.stage = destination.stage;
		}
		VkImageMemoryBarrier barrier{
			.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER,
			.srcAccessMask = source.access,
			.dstAccessMask = destination.access,
			.oldLayout = orhi::utils::EnumToValue<VkImageLayout>(p_oldLayout),
			.newLayout = orhi::utils::EnumToValue<VkImageLayout>(p_newLayout),
			.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED,
			.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED,
			.image = p_attachment.image.As<VkImage>(),
			.subresourceRange = {
				.aspectMask = orhi::utils::EnumToValue<VkImageAspectFlags>(p_attachment.aspectFlags),
				.baseMipLevel = 0,
				.levelCount = 1,
				.baseArrayLayer = 0,
				.layerCount = 1
			}
		};

		vkCmdPipelineBarrier(
			p_commandBuffer,
			source.stage,
			destination.stage,
			0,
			0, nullptr,
			0, nullptr,
			1, &barrier
		);
	}
}

namespace orhi
{
	template<>
	CommandBuffer::TCommandBuffer(
		impl::common::NativeHandle p_handle
	) : BackendObject{ p_handle }
	{

	}

	template<>
	CommandBuffer::TCommandBuffer(
		impl::common::NativeHandle p_handle,
		BackendTraits::CommandBufferContext p_context
	) :
		BackendObject{ p_handle },
		m_context{ p_context }
	{

	}

	template<>
	CommandBuffer::~TCommandBuffer()
	{

	}

	template<>
	void CommandBuffer::Reset()
	{
		const VkResult result = vkResetCommandBuffer(
			m_handle.As<VkCommandBuffer>(),
			0
		);
		ORHI_ASSERT(result == VK_SUCCESS, "failed to reset command buffer!");
		m_context.activeFramebuffer = nullptr;
	}

	template<>
	void CommandBuffer::Begin(types::ECommandBufferUsageFlags p_flags)
	{
		ORHI_ASSERT(m_context.activeFramebuffer == nullptr, "Cannot begin a command buffer while rendering is active");

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
		ORHI_ASSERT(m_context.activeFramebuffer == nullptr, "EndRendering must be called before ending the command buffer");
		VkResult result = vkEndCommandBuffer(m_handle.As<VkCommandBuffer>());
		ORHI_ASSERT(result == VK_SUCCESS, "failed to record command buffer!");
	}

	template<>
	void CommandBuffer::BeginRendering(const RenderingInfo<BackendTraits>& p_info)
	{
		ORHI_ASSERT(m_context.activeFramebuffer == nullptr, "Rendering is already active");
		ORHI_ASSERT(p_info.extent.width > 0 && p_info.extent.height > 0, "Rendering extent must be non-zero");

		const auto* framebuffer = p_info.framebuffer.GetNativeHandle().As<const FramebufferContext*>();
		ORHI_ASSERT(framebuffer != nullptr, "Framebuffer must have a valid native handle");
		ORHI_ASSERT(
			p_info.extent.width <= framebuffer->extent.width &&
			p_info.extent.height <= framebuffer->extent.height,
			"Rendering extent must fit within the framebuffer"
		);
		ORHI_ASSERT(!framebuffer->attachments.empty(), "Framebuffer must contain at least one attachment");
		ORHI_ASSERT(
			p_info.clearValues.size() <= framebuffer->attachments.size(),
			"Clear values must not exceed the number of framebuffer attachments"
		);

		const auto commandBuffer = m_handle.As<VkCommandBuffer>();
		std::vector<VkRenderingAttachmentInfoKHR> colorAttachments;
		std::vector<const FramebufferAttachment*> resolveAttachments;
		bool hasDepthAspect = false;
		bool hasStencilAspect = false;
		VkRenderingAttachmentInfoKHR depthStencilInfo{
			.sType = VK_STRUCTURE_TYPE_RENDERING_ATTACHMENT_INFO_KHR
		};

		for (size_t attachmentIndex = 0; attachmentIndex < framebuffer->attachments.size(); ++attachmentIndex)
		{
			const auto& attachment = framebuffer->attachments[attachmentIndex];
			const auto attachmentLayout = GetAttachmentLayout(attachment.type);
			const VkImageLayout layout = utils::EnumToValue<VkImageLayout>(attachmentLayout);
			TransitionAttachment(commandBuffer, attachment, attachment.initialLayout, attachmentLayout);

			if (attachment.type == types::EAttachmentType::COLOR)
			{
				VkRenderingAttachmentInfoKHR colorInfo{
					.sType = VK_STRUCTURE_TYPE_RENDERING_ATTACHMENT_INFO_KHR,
					.imageView = attachment.imageView.As<VkImageView>(),
					.imageLayout = layout,
					.loadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE,
					.storeOp = VK_ATTACHMENT_STORE_OP_STORE
				};

				if (attachmentIndex < p_info.clearValues.size())
				{
					const auto& clear = std::get<data::ColorClearValue>(p_info.clearValues.begin()[attachmentIndex]);
					colorInfo.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
					colorInfo.clearValue.color = { { clear.x, clear.y, clear.z, clear.w } };
				}

				colorAttachments.push_back(colorInfo);
			}
			else if (attachment.type == types::EAttachmentType::RESOLVE)
			{
				resolveAttachments.push_back(&attachment);
			}
			else
			{
				ORHI_ASSERT(depthStencilInfo.imageView == VK_NULL_HANDLE, "Only one depth/stencil attachment is supported");
				const auto aspects = utils::EnumToValue<VkImageAspectFlags>(attachment.aspectFlags);
				hasDepthAspect = (aspects & VK_IMAGE_ASPECT_DEPTH_BIT) != 0;
				hasStencilAspect = (aspects & VK_IMAGE_ASPECT_STENCIL_BIT) != 0;

				depthStencilInfo.imageView = attachment.imageView.As<VkImageView>();
				depthStencilInfo.imageLayout = layout;
				depthStencilInfo.loadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
				depthStencilInfo.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
				if (attachmentIndex < p_info.clearValues.size())
				{
					const auto& clear = std::get<data::DepthStencilClearValue>(p_info.clearValues.begin()[attachmentIndex]);
					depthStencilInfo.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
					depthStencilInfo.clearValue.depthStencil = { clear.depth, clear.stencil };
				}
			}
		}

		ORHI_ASSERT(!colorAttachments.empty() || hasDepthAspect || hasStencilAspect, "At least one rendering attachment is required");
		ORHI_ASSERT(
			resolveAttachments.empty() || resolveAttachments.size() == colorAttachments.size(),
			"Resolve attachments must match the color attachment count"
		);

		for (size_t i = 0; i < std::min(colorAttachments.size(), resolveAttachments.size()); ++i)
		{
			colorAttachments[i].resolveMode = GetColorResolveMode(resolveAttachments[i]->format);
			colorAttachments[i].resolveImageView = resolveAttachments[i]->imageView.As<VkImageView>();
			colorAttachments[i].resolveImageLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
		}

		VkRenderingInfoKHR renderingInfo{
			.sType = VK_STRUCTURE_TYPE_RENDERING_INFO_KHR,
			.renderArea = {
				.offset = { 0, 0 },
				.extent = { p_info.extent.width, p_info.extent.height }
			},
			.layerCount = 1,
			.colorAttachmentCount = static_cast<uint32_t>(colorAttachments.size()),
			.pColorAttachments = colorAttachments.data(),
			.pDepthAttachment = hasDepthAspect ? &depthStencilInfo : nullptr,
			.pStencilAttachment = hasStencilAspect ? &depthStencilInfo : nullptr
		};

		ORHI_ASSERT(m_context.beginRendering != nullptr, "Dynamic rendering entry point is not loaded");
		m_context.beginRendering(commandBuffer, &renderingInfo);
		m_context.activeFramebuffer = framebuffer;
	}

	template<>
	void CommandBuffer::EndRendering()
	{
		ORHI_ASSERT(m_context.activeFramebuffer != nullptr, "No rendering operation is active");

		const auto commandBuffer = m_handle.As<VkCommandBuffer>();
		ORHI_ASSERT(m_context.endRendering != nullptr, "Dynamic rendering entry point is not loaded");
		m_context.endRendering(commandBuffer);

		for (const auto& attachment : m_context.activeFramebuffer->attachments)
		{
			const auto attachmentLayout = GetAttachmentLayout(attachment.type);
			if (attachment.finalLayout == types::ETextureLayout::UNDEFINED || attachment.finalLayout == attachmentLayout)
			{
				continue;
			}

			TransitionAttachment(
				commandBuffer,
				attachment,
				attachmentLayout,
				attachment.finalLayout
			);
		}

		m_context.activeFramebuffer = nullptr;
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
	void CommandBuffer::PushConstants(
		PipelineLayout& p_pipelineLayout,
		types::EShaderStageFlags p_stageFlags,
		const data::MemoryRange& p_range,
		const void* p_data
	)
	{
		ORHI_ASSERT(p_data != nullptr, "PushConstants data pointer cannot be null");
		ORHI_ASSERT(p_range.size > 0ULL, "PushConstants range size must be greater than zero");
		ORHI_ASSERT(p_stageFlags != types::EShaderStageFlags::NONE, "PushConstants stage flags cannot be NONE");

		vkCmdPushConstants(
			m_handle.As<VkCommandBuffer>(),
			p_pipelineLayout.GetNativeHandle().As<VkPipelineLayout>(),
			utils::EnumToValue<VkShaderStageFlags>(p_stageFlags),
			static_cast<uint32_t>(p_range.offset),
			static_cast<uint32_t>(p_range.size),
			p_data
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
