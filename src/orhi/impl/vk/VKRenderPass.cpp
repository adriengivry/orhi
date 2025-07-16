/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#if defined(ORHI_COMPILE_VULKAN)

#include <orhi/impl/vk/RenderPass.h>

#include <orhi/debug/Assert.h>
#include <orhi/debug/Log.h>
#include <orhi/impl/vk/details/Types.h>

#include <vulkan/vulkan.h>

#include <unordered_map>

using namespace orhi::impl::vk;

namespace orhi
{
	template<>
	RenderPass::TRenderPass(
		Device& p_device,
		std::initializer_list<data::AttachmentDesc> p_attachments
	) : m_context{
		.device = p_device
	}
	{
		std::vector<VkAttachmentDescription> attachments;
		std::unordered_map<types::EAttachmentType, std::vector<VkAttachmentReference>> attachmentsRefs;

		attachmentsRefs[types::EAttachmentType::COLOR] = {};
		attachmentsRefs[types::EAttachmentType::DEPTH_STENCIL] = {};
		attachmentsRefs[types::EAttachmentType::RESOLVE] = {};

		uint32_t attachmentIndex = 0;

		for (const auto& attachment : p_attachments)
		{
			attachments.push_back(VkAttachmentDescription{
				.format = utils::EnumToValue<VkFormat>(attachment.format),
				.samples = static_cast<VkSampleCountFlagBits>(utils::EnumToValue<VkSampleCountFlags>(attachment.samples)),
				.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR,
				.storeOp = VK_ATTACHMENT_STORE_OP_STORE,
				.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE,
				.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE,
				.initialLayout = utils::EnumToValue<VkImageLayout>(attachment.initialLayout),
				.finalLayout = utils::EnumToValue<VkImageLayout>(attachment.finalLayout)
			});

			const auto layout = attachment.type == types::EAttachmentType::DEPTH_STENCIL
				? VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL
				: VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

			attachmentsRefs[attachment.type].push_back(VkAttachmentReference{
				.attachment = attachmentIndex++,
				.layout = layout
			});
		}

		ORHI_ASSERT(
			attachmentsRefs[types::EAttachmentType::DEPTH_STENCIL].size() <= 1,
			"Only one depth/stencil attachment is allowed per render pass!"
		);

		VkSubpassDescription subpass{
			.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS,
			.colorAttachmentCount = static_cast<uint32_t>(attachmentsRefs[types::EAttachmentType::COLOR].size()),
			// The index of the attachment in this array is directly referenced from the fragment shader
			// with the layout(location = 0) out vec4 outColor directive!
			// Here we have an array of one element (no actual array, just ptr to element)
			.pColorAttachments = attachmentsRefs[types::EAttachmentType::COLOR].data(),
			.pResolveAttachments = attachmentsRefs[types::EAttachmentType::RESOLVE].data(),
			.pDepthStencilAttachment = attachmentsRefs[types::EAttachmentType::DEPTH_STENCIL].data()
		};

		VkPipelineStageFlags stageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
		VkAccessFlags accessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;

		if (!attachmentsRefs[types::EAttachmentType::DEPTH_STENCIL].empty())
		{
			stageMask |= VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT;
			accessMask |= VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;
		}

		VkSubpassDependency dependency{
			.srcSubpass = VK_SUBPASS_EXTERNAL,
			.dstSubpass = 0,
			.srcStageMask = stageMask,
			.dstStageMask = stageMask,
			.srcAccessMask = 0,
			.dstAccessMask = accessMask,
		};

		VkRenderPassCreateInfo createInfo{
			.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO,
			.attachmentCount = static_cast<uint32_t>(attachments.size()),
			.pAttachments = attachments.data(),
			.subpassCount = 1,
			.pSubpasses = &subpass,
			.dependencyCount = 1,
			.pDependencies = &dependency
		};

		VkResult result = vkCreateRenderPass(
			m_context.device.GetNativeHandle().As<VkDevice>(),
			&createInfo,
			nullptr,
			&m_handle.ReinterpretAs<VkRenderPass&>()
		);
		
		ORHI_ASSERT(result == VK_SUCCESS, "failed to create render pass!");
	}

	template<>
	RenderPass::~TRenderPass()
	{
		vkDestroyRenderPass(
			m_context.device.GetNativeHandle().As<VkDevice>(),
			m_handle.As<VkRenderPass>(),
			nullptr
		);
	}
}

template class orhi::api::TRenderPass<orhi::impl::vk::BackendTraits>;

#endif // #if defined(ORHI_COMPILE_VULKAN)
