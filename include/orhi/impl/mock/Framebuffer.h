/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <unordered_map>

#include <orhi/api/TFramebuffer.h>
#include <orhi/impl/mock/Texture.h>
#include <orhi/impl/mock/Renderbuffer.h>

namespace orhi::impl::mock
{
	template<types::EGraphicsBackend Backend, class TextureContext, class TextureHandleContext, class RenderbufferContext>
	struct TFramebufferContext
	{
		using Attachment = api::TFramebufferAttachment<Backend, TextureContext, TextureHandleContext, RenderbufferContext>;

		bool valid = false;
		std::string debugName = "";
		std::unordered_map<std::underlying_type_t<types::EFramebufferAttachment>, Attachment> attachments;
	};

	using FramebufferContext = TFramebufferContext<
		types::EGraphicsBackend::NONE,
		TextureContext,
		TextureHandleContext,
		RenderbufferContext
	>;

	using Framebuffer = api::TFramebuffer<
		types::EGraphicsBackend::NONE,
		FramebufferContext,
		TextureContext,
		TextureHandleContext,
		RenderbufferContext
	>;
}
