/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#if defined(ORHI_COMPILE_MOCK)

#include <orhi/debug/Assert.h>

#include <orhi/impl/mock/Texture.h>

using namespace orhi::impl::mock;

namespace orhi
{
	template<>
	Texture::TTexture(types::ETextureType p_type, std::string_view p_debugName) : TTextureHandle{ p_type, 0 }
	{
		m_textureContext.debugName = p_debugName;
	}

	template<>
	Texture::~TTexture()
	{
	}

	template<>
	void Texture::Allocate(const data::TextureDesc& p_desc)
	{
		m_textureContext.desc = p_desc;
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

		if (IsMutable())
		{
			auto& mutableDesc = m_textureContext.desc.mutableDesc.value();
			mutableDesc.format = p_format;
			mutableDesc.type = p_type;
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
	}

	template<>
	void Texture::SetBorderColor(const math::Vec4& p_color)
	{
		ORHI_ASSERT(IsValid(), "Cannot set border color for a texture before it has been allocated");
	}
}

#endif // #if defined(ORHI_COMPILE_MOCK)
