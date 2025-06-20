/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <unordered_map>

#include <orhi/api/TFramebuffer.h>
#include <orhi/impl/gl/Texture.h>
#include <orhi/impl/gl/Renderbuffer.h>

namespace orhi::impl::gl
{
	template<types::EGraphicsBackend Backend, class TextureContext, class TextureHandleContext, class RenderbufferContext>
	struct TFramebufferContext
	{
		using Attachment = api::TFramebufferAttachment<Backend, TextureContext, TextureHandleContext, RenderbufferContext>;

		uint32_t id = 0;
		bool valid = false;
		std::string debugName;
		std::unordered_map<uint32_t, Attachment> attachments;
	};

	using FramebufferContext = TFramebufferContext<
		types::EGraphicsBackend::OPENGL,
		TextureContext,
		TextureHandleContext,
		RenderbufferContext
	>;

	using Framebuffer = api::TFramebuffer<
		types::EGraphicsBackend::OPENGL,
		FramebufferContext,
		TextureContext,
		TextureHandleContext,
		RenderbufferContext
	>;
}
