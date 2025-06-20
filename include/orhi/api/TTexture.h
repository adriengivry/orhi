/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <string>

#include <orhi/math/Vec4.h>
#include <orhi/api/TTextureHandle.h>
#include <orhi/types/EGraphicsBackend.h>
#include <orhi/data/TextureDesc.h>

namespace orhi::api
{
	/**
	* Represents a texture, used to store image data for the graphics backend to use.
	*/
	template<types::EGraphicsBackend Backend, class TextureContext, class TextureHandleContext>
	class TTexture final : public TTextureHandle<Backend, TextureHandleContext>
	{
	public:
		/**
		* Creates a texture.
		* @param p_type The type of the texture (2D, Cube, etc.)
		* @param p_debugName A name used to identify the texture for debugging purposes
		*/
		TTexture(types::ETextureType p_type, std::string_view p_debugName = std::string_view{});

		/**
		* Destroys the texture.
		*/
		~TTexture();

		/**
		* Allocates memory for the texture.
		* @param p_desc
		*/
		void Allocate(const data::TextureDesc& p_desc);

		/**
		* Returns true if the texture has been properly allocated.
		*/
		bool IsValid() const;

		/**
		* Returns true if the texture is mutable.
		*/
		bool IsMutable() const;

		/**
		* Uploads data to the texture.
		* @param p_data Pointer to the data to upload.
		* @param p_format Format of the data.
		* @param p_type Type of the pixel data.
		*/
		void Upload(const void* p_data, types::EFormat p_format, types::EPixelDataType p_type);

		/**
		* Resizes the texture.
		* @param p_width
		* @param p_height
		*/
		void Resize(uint32_t p_width, uint32_t p_height);

		/**
		* Returns the texture descriptor structure.
		*/
		const data::TextureDesc& GetDesc() const;

		/**
		* Generates mipmaps for the texture.
		*/
		void GenerateMipmaps() const;

		/**
		* Sets the border color for the texture.
		* @param p_color
		*/
		void SetBorderColor(const math::Vec4& p_color);

		/**
		* Returns the debug name of the texture.
		*/
		const std::string& GetDebugName() const;

	private:
		TextureContext m_textureContext;
	};
}
