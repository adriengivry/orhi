/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/api/TSwapChain.h>
#include <orhi/impl/vk/Framebuffer.h>
#include <orhi/impl/vk/Device.h>
#include <orhi/data/SwapChainDesc.h>
#include <orhi/impl/vk/VulkanContextRegistry.h>

struct VkSwapchainKHR_T;
typedef VkSwapchainKHR_T* VkSwapchainKHR;

struct VkImage_T;
typedef VkImage_T* VkImage;

struct VkImageView_T;
typedef VkImageView_T* VkImageView;

namespace orhi::impl::vk
{
	struct SwapChainContext
	{
		Device& device;
		data::SwapChainDesc desc;
		VkSwapchainKHR handle;
		std::vector<VkImage> images;
		std::vector<VkImageView> imageViews;
		std::pair<uint32_t, uint32_t> extent;
	};

	using SwapChain = api::TSwapChain<types::EGraphicsBackend::VULKAN, VulkanContextRegistry>;
}
