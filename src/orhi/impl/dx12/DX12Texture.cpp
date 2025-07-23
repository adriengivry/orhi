/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry, Jian Bang Xu
* @licence: MIT
*/

#if defined(ORHI_COMPILE_DX12)

#include <orhi/impl/dx12/Texture.h>

#include <orhi/debug/Assert.h>
#include <orhi/debug/Log.h>
#include <orhi/impl/dx12/detail/Types.h>

#include <d3d12.h>
#include <dxgi1_6.h>

using namespace orhi::impl::dx12;

namespace orhi
{
	template<>
	Texture::TTexture(
		Device& p_device,
		const data::TextureDesc& p_desc
	)
	{
		
	}

	template<>
	Texture::~TTexture()
	{
		
	}

	template<>
	bool Texture::IsAllocated() const
	{
		return false;
	}

	template<>
	void Texture::Allocate(types::EMemoryPropertyFlags p_properties)
	{
		
	}

	template<>
	void Texture::Deallocate()
	{
		
	}

	template<>
	uint64_t Texture::GetAllocatedBytes() const
	{
		return 0;
	}
}

template class orhi::api::TTexture<orhi::impl::dx12::BackendTraits>;

#endif // #if defined(ORHI_COMPILE_DX12)
