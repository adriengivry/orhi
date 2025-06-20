/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#if defined(ORHI_COMPILE_OPENGL)

#include <orhi/debug/Assert.h>
#include <orhi/debug/Log.h>
#include <orhi/impl/gl/details/glad/glad.h>
#include <orhi/impl/gl/details/Types.h>
#include <orhi/impl/gl/Texture.h>

using namespace orhi::impl::gl;

namespace
{
	constexpr uint32_t CalculateMipMapLevels(uint32_t p_width, uint32_t p_height)
	{
		uint32_t maxDim = p_width > p_height ? p_width : p_height;
		return maxDim ? 32u - __lzcnt(maxDim) : 1u;
	}

	constexpr bool IsValidMipMapFilter(orhi::types::ETextureFilteringMode p_mode)
	{
		return
			p_mode == orhi::types::ETextureFilteringMode::NEAREST_MIPMAP_NEAREST ||
			p_mode == orhi::types::ETextureFilteringMode::NEAREST_MIPMAP_LINEAR ||
			p_mode == orhi::types::ETextureFilteringMode::LINEAR_MIPMAP_NEAREST ||
			p_mode == orhi::types::ETextureFilteringMode::LINEAR_MIPMAP_LINEAR;
	}
}

namespace orhi
{
	template<>
	Texture::TTexture(types::ETextureType p_type, std::string_view p_debugName) : TextureHandle(p_type)
	{
		glCreateTextures(m_context.type, 1, &m_context.id);
		m_textureContext.debugName = p_debugName;
	}

	template<>
	Texture::~TTexture()
	{
		glDeleteTextures(1, &m_context.id);
	}

	template<>
	void Texture::Allocate(const data::TextureDesc& p_desc)
	{
		auto& desc = m_textureContext.desc;

		desc = p_desc;
		desc.width = std::max(1u, desc.width);
		desc.height = std::max(1u, desc.height);

		if (desc.mutableDesc.has_value())
		{
			const auto& mutableDesc = desc.mutableDesc.value();

			ORHI_ASSERT(m_context.type == GL_TEXTURE_2D, "Mutable textures are only supported for 2D textures");

			// No DSA version for glTexImage2D (mutable texture),
			// so we need to Bind/Unbind the texture.
			Bind();
			glTexImage2D(
				m_context.type,
				0,
				details::EnumToValue<GLenum>(desc.internalFormat),
				desc.width,
				desc.height,
				0,
				details::EnumToValue<GLenum>(mutableDesc.format),
				details::EnumToValue<GLenum>(mutableDesc.type),
				mutableDesc.data
			);
			Unbind();
		}
		else
		{
			// If the underlying texture is a cube map, this will allocate all 6 sides.
			// No need to iterate over each side.
			glTextureStorage2D(
				m_context.id,
				desc.useMipMaps ? CalculateMipMapLevels(desc.width, desc.height) : 1,
				details::EnumToValue<GLenum>(desc.internalFormat),
				desc.width,
				desc.height
			);
		}

		// Once the texture is allocated, we don't need to set the parameters again
		if (!m_textureContext.allocated)
		{
			glTextureParameteri(m_context.id, GL_TEXTURE_WRAP_S, details::EnumToValue<GLenum>(p_desc.horizontalWrap));
			glTextureParameteri(m_context.id, GL_TEXTURE_WRAP_T, details::EnumToValue<GLenum>(p_desc.verticalWrap));
			glTextureParameteri(m_context.id, GL_TEXTURE_MIN_FILTER, details::EnumToValue<GLenum>(p_desc.minFilter));
			glTextureParameteri(m_context.id, GL_TEXTURE_MAG_FILTER, details::EnumToValue<GLenum>(p_desc.magFilter));
		}

		m_textureContext.allocated = true;
	}

	template<>
	bool Texture::IsValid() const
	{
		return m_textureContext.allocated;
	}

	template<>
	bool Texture::IsMutable() const
	{
		ORHI_ASSERT(IsValid(), "Cannot check if a texture is mutable before it has been allocated");
		return m_textureContext.desc.mutableDesc.has_value();
	}

	template<>
	void Texture::Upload(const void* p_data, types::EFormat p_format, types::EPixelDataType p_type)
	{
		ORHI_ASSERT(IsValid(), "Cannot upload data to a texture before it has been allocated");
		ORHI_ASSERT(p_data, "Cannot upload texture data from a null pointer");

		if (IsMutable())
		{
			m_textureContext.desc.mutableDesc.value().data = p_data;
			Allocate(m_textureContext.desc);
		}
		else
		{
			if (m_context.type == GL_TEXTURE_CUBE_MAP)
			{
				for (uint32_t i = 0; i < 6; ++i)
				{
					glTextureSubImage3D(
						m_context.id,
						0,
						0,
						0,
						0,
						m_textureContext.desc.width,
						m_textureContext.desc.height,
						i,
						details::EnumToValue<GLenum>(p_format),
						details::EnumToValue<GLenum>(p_type),
						p_data
					);
				}
			}
			else
			{
				glTextureSubImage2D(
					m_context.id,
					0,
					0,
					0,
					m_textureContext.desc.width,
					m_textureContext.desc.height,
					details::EnumToValue<GLenum>(p_format),
					details::EnumToValue<GLenum>(p_type),
					p_data
				);
			}
		}
	}

	template<>
	void Texture::Resize(uint32_t p_width, uint32_t p_height)
	{
		ORHI_ASSERT(IsValid(), "Cannot resize a texture before it has been allocated");
		ORHI_ASSERT(IsMutable(), "Cannot resize an immutable texture");

		auto& desc = m_textureContext.desc;

		if (p_width != desc.width || p_height != desc.width)
		{
			desc.width = p_width;
			desc.height = p_height;

			Allocate(desc);
		}
	}

	template<>
	const orhi::data::TextureDesc& Texture::GetDesc() const
	{
		ORHI_ASSERT(IsValid(), "Cannot get the descriptor of a texture before it has been allocated");
		return m_textureContext.desc;
	}

	template<>
	void Texture::GenerateMipmaps() const
	{
		ORHI_ASSERT(IsValid(), "Cannot generate mipmaps for a texture before it has been allocated");
		ORHI_ASSERT(m_textureContext.desc.useMipMaps, "Cannot generate mipmaps for a texture that doesn't use them");

		if (IsValidMipMapFilter(m_textureContext.desc.minFilter))
		{
			glGenerateTextureMipmap(m_context.id);
		}
		else
		{
			// In the event a user tries to generate mipmaps for a texture that doesn't use a valid mipmap filter
			ORHI_LOG_ERROR("Cannot generate mipmaps for a texture that doesn't use a valid mipmap filter");
		}
	}

	template<>
	void Texture::SetBorderColor(const math::Vec4& p_color)
	{
		ORHI_ASSERT(IsValid(), "Cannot set border color for a texture before it has been allocated");
		glTextureParameterfv(m_context.id, GL_TEXTURE_BORDER_COLOR, &p_color.x);
	}

	template<>
	const std::string& Texture::GetDebugName() const
	{
		return m_textureContext.debugName;
	}
}

#endif // #if defined(ORHI_COMPILE_OPENGL)
