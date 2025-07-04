/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#if defined(ORHI_COMPILE_VULKAN)

#include <orhi/debug/Assert.h>
#include <orhi/debug/Log.h>
#include <orhi/impl/vk/RenderPass.h>
#include <vulkan/vulkan.h>

using namespace orhi::impl::vk;

namespace orhi
{
	template<>
	RenderPass::TRenderPass(
		Device& p_device,
		types::EFormat p_format
	) : m_context{
		.device = p_device,
		.handle = VK_NULL_HANDLE
	}
	{
		VkAttachmentDescription colorAttachment{
			.format = static_cast<VkFormat>(p_format), // TODO: Add proper conversion
			.samples = VK_SAMPLE_COUNT_1_BIT,
			.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR,
			.storeOp = VK_ATTACHMENT_STORE_OP_STORE,
			.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE,
			.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE,
			.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED,
			.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR
		};

		VkAttachmentReference colorAttachmentRef{
			.attachment = 0,
			.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL
		};

		VkSubpassDescription subpass{
			.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS,
			.colorAttachmentCount = 1,
			// The index of the attachment in this array is directly referenced from the fragment shader
			// with the layout(location = 0) out vec4 outColor directive!
			// Here we have an array of one element (no actual array, just ptr to element)
			.pColorAttachments = &colorAttachmentRef
		};

		VkSubpassDependency dependency{
			.srcSubpass = VK_SUBPASS_EXTERNAL,
			.dstSubpass = 0,
			.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
			.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
			.srcAccessMask = 0,
			.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT,
		};

		VkRenderPassCreateInfo createInfo{
			.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO,
			.attachmentCount = 1,
			.pAttachments = &colorAttachment,
			.subpassCount = 1,
			.pSubpasses = &subpass,
			.dependencyCount = 1,
			.pDependencies = &dependency
		};

		VkResult result = vkCreateRenderPass(
			m_context.device.GetNativeHandle().As<VkDevice>(),
			&createInfo,
			nullptr,
			&m_context.handle
		);
		
		ORHI_ASSERT(result == VK_SUCCESS, "failed to create render pass!");
	}

	template<>
	RenderPass::~TRenderPass()
	{
		vkDestroyRenderPass(
			m_context.device.GetNativeHandle().As<VkDevice>(),
			m_context.handle,
			nullptr
		);
	}

	template<>
	data::NativeHandle RenderPass::GetNativeHandle() const
	{
		return m_context.handle;
	}
}

#endif // #if defined(ORHI_COMPILE_VULKAN)
