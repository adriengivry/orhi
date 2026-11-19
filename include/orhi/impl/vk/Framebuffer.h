/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/api/TFramebuffer.h>
#include <orhi/impl/common/NativeHandle.h>
#include <orhi/impl/vk/BackendTraits.h>
#include <orhi/impl/vk/Device.h>
#include <orhi/math/Extent2D.h>
#include <orhi/types/EAttachmentType.h>
#include <orhi/types/EFormat.h>
#include <orhi/types/ETextureAspectFlags.h>
#include <orhi/types/ETextureLayout.h>

#include <vector>

namespace orhi::impl::vk
{
	struct FramebufferAttachment
	{
		common::NativeHandle image;
		common::NativeHandle imageView;
		types::EAttachmentType type;
		types::EFormat format;
		types::ETextureLayout initialLayout;
		types::ETextureLayout finalLayout;
		types::ETextureAspectFlags aspectFlags;
	};

	struct FramebufferContext
	{
		Device& device;
		math::Extent2D extent;
		std::vector<FramebufferAttachment> attachments;
	};

	using Framebuffer = api::TFramebuffer<BackendTraits>;
}
