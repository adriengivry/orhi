/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <memory>
#include <variant>
#include <optional>

#include <orhi/data/PipelineState.h>
#include <orhi/api/TTexture.h>
#include <orhi/api/TRenderbuffer.h>
#include <orhi/types/ERenderingCapability.h>
#include <orhi/types/EPrimitiveMode.h>
#include <orhi/types/ERasterizationMode.h>
#include <orhi/types/EComparaisonAlgorithm.h>
#include <orhi/types/EOperation.h>
#include <orhi/types/ECullFace.h>
#include <orhi/types/EPixelDataFormat.h>
#include <orhi/types/EPixelDataType.h>
#include <orhi/types/EGraphicsBackend.h>
#include <orhi/types/EFramebufferAttachment.h>

namespace orhi::api
{
	template<types::EGraphicsBackend Backend, class TextureContext, class TextureHandleContext, class RenderBufferContext>
	using TFramebufferAttachment = std::variant<
		std::shared_ptr<TTexture<Backend, TextureContext, TextureHandleContext>>,
		std::shared_ptr<TRenderbuffer<Backend, RenderBufferContext>>
	>;

	/**
	* Represents a framebuffer, used to store render data for the graphics backend to use.
	*/
	template<types::EGraphicsBackend Backend, class FramebufferContext, class TextureContext, class TextureHandleContext, class RenderBufferContext>
	class TFramebuffer
	{
	public:
		using Attachment = TFramebufferAttachment<Backend, TextureContext, TextureHandleContext, RenderBufferContext>;

		template<typename T>
		static constexpr bool IsSupportedAttachmentType =
			std::same_as<T, TTexture<Backend, TextureContext, TextureHandleContext>> ||
			std::same_as<T, TRenderbuffer<Backend, RenderBufferContext>>;

		/**
		* Creates a framebuffer.
		* @param p_debugName A name used to identify the framebuffer for debugging purposes
		*/
		TFramebuffer(std::string_view p_debugName = std::string_view{});

		/**
		* Destroys the framebuffer.
		*/
		~TFramebuffer();

		/**
		* Binds the framebuffer.
		*/
		void Bind() const;

		/**
		* Unbinds the framebuffer.
		*/
		void Unbind() const;

		/**
		* Validate the framebuffer. Must be executed at least once after the framebuffer creation.
		* @note It's recommended to call this method after each attachment change.
		* @return Returns true if the framebuffer has been validated successfully.
		*/
		bool Validate();

		/**
		* Returns true if the framebuffer is valid.
		*/
		bool IsValid() const;

		/**
		* Resizes all attachments to match the given width and height.
		* @param p_width
		* @param p_height
		*/
		void Resize(uint16_t p_width, uint16_t p_height);

		/**
		* Attaches the given texture or render buffer to the framebuffer, at the given attachment point
		* @param p_toAttach must be a texture or a render buffer.
		* @param p_attachment
		* @param p_index (optional) useful when specifying multiple color attachments.
		* @param p_layer (optional) useful when specifying multiple layers in a texture (e.g. cubemap or 3D texture).
		*/
		template<class T>
			requires IsSupportedAttachmentType<T>
		void Attach(std::shared_ptr<T> p_toAttach,
			types::EFramebufferAttachment p_attachment,
			uint32_t p_index = 0,
			std::optional<uint32_t> p_layer = std::nullopt
		);

		/**
		* Returns the texture or render buffer associated with the given attachment point.
		* @param p_attachment
		* @param p_index (optional) useful when specifying multiple color attachments.
		*/
		template<class T>
			requires IsSupportedAttachmentType<T>
		std::optional<std::reference_wrapper<T>> GetAttachment(
			orhi::types::EFramebufferAttachment p_attachment,
			uint32_t p_index = 0
		) const;

		/**
		* Selects which color attachment to draw to.
		* @param p_index index of the color attachment, if set to std::nullopt, no color will be drawn.
		*/
		void SetTargetDrawBuffer(std::optional<uint32_t> p_index);

		/**
		* Selects which color attachment to read from.
		* @param p_index index of the color attachment, if set to std::nullopt, no color attachment will be available for read.
		*/
		void SetTargetReadBuffer(std::optional<uint32_t> p_index);

		/**
		* Returns the ID the buffer.
		*/
		uint32_t GetID() const;

		/**
		* Returns the size of the given attachment.
		* @param p_attachment
		*/
		std::pair<uint16_t, uint16_t> GetSize(
			types::EFramebufferAttachment p_attachment = types::EFramebufferAttachment::COLOR
		) const;

		/**
		* Blits the framebuffer to the back buffer.
		* @param p_backBufferWidth
		* @param p_backBufferHeight
		*/
		void BlitToBackBuffer(uint16_t p_backBufferWidth, uint16_t p_backBufferHeight) const;

		/**
		* Reads pixels from the framebuffer.
		* @param p_x The x-coordinate of the lower-left corner.
		* @param p_y The y-coordinate of the lower-left corner.
		* @param p_width The width of the pixel rectangle.
		* @param p_height The height of the pixel rectangle.
		* @param p_format The format of the pixel data.
		* @param p_type The data type of the pixel data.
		* @param p_data The destination buffer to store pixel data.
		*/
		void ReadPixels(
			uint32_t p_x,
			uint32_t p_y,
			uint32_t p_width,
			uint32_t p_height,
			types::EPixelDataFormat p_format,
			types::EPixelDataType p_type,
			void* p_data
		) const;

		/**
		* Returns the debug name of the framebuffer.
		*/
		const std::string& GetDebugName() const;

	protected:
		FramebufferContext m_context;
	};
}
