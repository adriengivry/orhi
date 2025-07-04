/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/api/TSwapChain.h>
#include <orhi/impl/vk/Framebuffer.h>
#include <orhi/impl/vk/Device.h>
#include <orhi/impl/vk/RenderPass.h>
#include <orhi/impl/vk/Semaphore.h>
#include <orhi/impl/vk/Fence.h>
#include <orhi/data/SwapChainDesc.h>

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

	using SwapChain = api::TSwapChain<
		types::EGraphicsBackend::VULKAN,
		SwapChainContext,
		DeviceContext,
		FramebufferContext,
		RenderPassContext,
		SemaphoreContext,
		FenceContext
	>;
}
