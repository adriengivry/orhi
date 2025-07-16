/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/api/TSwapChain.h>
#include <orhi/data/SwapChainDesc.h>
#include <orhi/impl/vk/BackendTraits.h>
#include <orhi/impl/vk/Descriptor.h>
#include <orhi/impl/vk/Device.h>
#include <orhi/impl/vk/Framebuffer.h>

#include <deque>

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
		std::vector<VkImage> images;
		std::deque<Descriptor> imageDescriptors;
		math::Extent2D extent;
	};

	using SwapChain = api::TSwapChain<BackendTraits>;
}
