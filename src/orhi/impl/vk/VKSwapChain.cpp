/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#if defined(ORHI_COMPILE_VULKAN)

#include <orhi/impl/vk/SwapChain.h>

#include <orhi/data/TextureViewDesc.h>
#include <orhi/debug/Assert.h>
#include <orhi/debug/Log.h>
#include <orhi/except/OutOfDateSwapChain.h>
#include <orhi/impl/vk/Descriptor.h>
#include <orhi/impl/vk/Fence.h>
#include <orhi/impl/vk/RenderPass.h>
#include <orhi/impl/vk/Semaphore.h>
#include <orhi/impl/vk/details/Types.h>

#include <vulkan/vulkan.h>

#include <array>

using namespace orhi::impl::vk;

namespace
{
	uint32_t CalculateSwapChainImageCount(const orhi::data::SwapChainDesc& p_desc)
	{
		// Simply sticking to this minimum means that we may sometimes have to wait on the driver
		// to complete internal operations before we can acquire another image to render to.
		// Therefore it is recommended to request at least one more image than the minimum:
		const uint32_t minImageCount = p_desc.minImageCount + 1;
		const uint32_t maxImageCount = p_desc.maxImageCount;

		if (maxImageCount > 0 && minImageCount > maxImageCount)
		{
			return maxImageCount;
		}

		return minImageCount;
	}
}

namespace orhi
{
	template<>
	SwapChain::TSwapChain(
		Device& p_device,
		data::NativeHandle p_surface,
		const math::Extent2D& p_windowSize,
		const data::SwapChainDesc& p_desc,
		std::optional<std::reference_wrapper<SwapChain>> p_oldSwapChain
	) : m_context{
		.device = p_device,
		.desc = p_desc,
		.extent = p_windowSize
	}
	{
		const auto& indices = m_context.device.GetQueuesDesc().indices;

		VkSwapchainCreateInfoKHR createInfo{
			.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR,
			.surface = p_surface.As<VkSurfaceKHR>(),
			.minImageCount = CalculateSwapChainImageCount(m_context.desc),
			.imageFormat = utils::EnumToValue<VkFormat>(m_context.desc.format),
			.imageColorSpace = utils::EnumToValue<VkColorSpaceKHR>(m_context.desc.colorSpace),
			.imageExtent = reinterpret_cast<VkExtent2D&>(m_context.extent),
			.imageArrayLayers = 1, // always 1 unless we're developing a stereoscopic 3D application.

			// It is also possible that we'll render images to a separate image first to perform operations like post-processing.
			// In that case we may use a value like VK_IMAGE_USAGE_TRANSFER_DST_BIT instead and use a memory operation to transfer
			// the rendered image to a swap chain image.
			.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT,

			// Specify how to handle swap chain images that will be used across multiple queue families.
			// That will be the case in our application if the graphics queue family is different from the presentation queue.
			// We'll be drawing on the images in the swap chain from the graphics queue and then submitting them on the presentation queue. 
			// 
			//	VK_SHARING_MODE_EXCLUSIVE: An image is owned by one queue family at a time and ownership must be explicitly transferred before using it in another queue family.This option offers the best performance.
			//	VK_SHARING_MODE_CONCURRENT : Images can be used across multiple queue families without explicit ownership transfers.
			//
			.imageSharingMode = indices.size() > 1 ? VK_SHARING_MODE_CONCURRENT : VK_SHARING_MODE_EXCLUSIVE,
			.queueFamilyIndexCount = indices.size() > 1 ? static_cast<uint32_t>(indices.size()) : 0,
			.pQueueFamilyIndices = indices.size() > 1 ? indices.data() : VK_NULL_HANDLE,

			.preTransform = static_cast<VkSurfaceTransformFlagBitsKHR>(
				utils::EnumToValue<VkSurfaceTransformFlagsKHR>(m_context.desc.currentTransform)
			),

			// The compositeAlpha field specifies if the alpha channel should be used for blending with other windows in the window system. You'll almost always want to simply ignore the alpha channel, hence VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR.
			.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR,
			.presentMode = utils::EnumToValue<VkPresentModeKHR>(m_context.desc.presentMode),
			.clipped = VK_TRUE,
			.oldSwapchain =
				p_oldSwapChain ?
				p_oldSwapChain.value().get().GetNativeHandle().As<VkSwapchainKHR>() :
				VK_NULL_HANDLE
		};

		VkResult result = vkCreateSwapchainKHR(
			m_context.device.GetNativeHandle().As<VkDevice>(),
			&createInfo,
			nullptr,
			&m_handle.ReinterpretAs<VkSwapchainKHR&>()
		);

		ORHI_ASSERT(result == VK_SUCCESS, "failed to create swap chain!");

		// Retrieve images
		uint32_t imageCount;
		vkGetSwapchainImagesKHR(
			m_context.device.GetNativeHandle().As<VkDevice>(),
			m_handle.As<VkSwapchainKHR>(),
			&imageCount,
			nullptr
		);

		m_context.images.resize(imageCount);
		vkGetSwapchainImagesKHR(
			m_context.device.GetNativeHandle().As<VkDevice>(),
			m_handle.As<VkSwapchainKHR>(),
			&imageCount,
			m_context.images.data()
		);

		// Create image views
		m_context.imageDescriptors.reserve(m_context.images.size());

		for (size_t i = 0; i < m_context.images.size(); i++)
		{
			m_context.imageDescriptors.emplace_back(
				m_context.device,
				data::TextureViewDesc{
					.texture = m_context.images[i],
					.format = m_context.desc.format,
					.type = types::ETextureType::TEXTURE_2D,
					.aspectFlags = types::ETextureAspectFlags::COLOR,
				}
			);
			/*
			VkImageViewCreateInfo createInfo{
				.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
				.image = m_context.images[i],
				.viewType = VK_IMAGE_VIEW_TYPE_2D,
				.format = utils::EnumToValue<VkFormat>(m_context.desc.format),
				.components = {
					.r = VK_COMPONENT_SWIZZLE_IDENTITY,
					.g = VK_COMPONENT_SWIZZLE_IDENTITY,
					.b = VK_COMPONENT_SWIZZLE_IDENTITY,
					.a = VK_COMPONENT_SWIZZLE_IDENTITY
				},
				.subresourceRange = {
					.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
					.baseMipLevel = 0,
					.levelCount = 1,
					.baseArrayLayer = 0,
					.layerCount = 1
				}
			};

			VkResult imageCreationResult = vkCreateImageView(
				m_context.device.GetNativeHandle().As<VkDevice>(),
				&createInfo,
				nullptr,
				&m_context.imageViews[i]
			);

			ORHI_ASSERT(imageCreationResult == VK_SUCCESS, "Failed to create image view");
			*/
		}
	}

	template<>
	SwapChain::~TSwapChain()
	{
		m_context.imageDescriptors.clear();

		vkDestroySwapchainKHR(
			m_context.device.GetNativeHandle().As<VkDevice>(),
			m_handle.As<VkSwapchainKHR>(),
			nullptr
		);
	}

	template<>
	uint32_t SwapChain::GetImageCount() const
	{
		return static_cast<uint32_t>(m_context.images.size());
	}

	template<>
	Descriptor& SwapChain::GetImageDescriptor(uint32_t p_index)
	{
		return m_context.imageDescriptors[p_index];
	}

	template<>
	uint32_t SwapChain::AcquireNextImage(
		std::optional<std::reference_wrapper<Semaphore>> p_semaphore,
		std::optional<std::reference_wrapper<Fence>> p_fence,
		std::optional<uint64_t> p_timeout
	)
	{
		uint32_t imageIndex;

		VkResult result = vkAcquireNextImageKHR(
			m_context.device.GetNativeHandle().As<VkDevice>(),
			m_handle.As<VkSwapchainKHR>(),
			p_timeout.value_or(UINT64_MAX),
			p_semaphore.has_value() ? p_semaphore->get().GetNativeHandle().As<VkSemaphore>() : VK_NULL_HANDLE,
			p_fence.has_value() ? p_fence->get().GetNativeHandle().As<VkFence>() : VK_NULL_HANDLE,
			&imageIndex
		);

		if (result == VK_ERROR_OUT_OF_DATE_KHR)
		{
			throw except::OutOfDateSwapChain();
		}

		ORHI_ASSERT(result == VK_SUCCESS, "failed to acquire next image");

		return imageIndex;
	}
}

template class orhi::api::TSwapChain<orhi::impl::vk::BackendTraits>;

#endif // #if defined(ORHI_COMPILE_VULKAN)
