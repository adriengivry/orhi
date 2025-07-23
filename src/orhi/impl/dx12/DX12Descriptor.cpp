/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry, Jian Bang Xu
* @licence: MIT
*/

#if defined(ORHI_COMPILE_DX12)

#include <orhi/impl/dx12/Descriptor.h>

#include <orhi/debug/Assert.h>
#include <orhi/debug/Log.h>
#include <orhi/impl/dx12/detail/Types.h>
#include <orhi/impl/dx12/Device.h>
#include <orhi/impl/dx12/Texture.h>

#include <d3d12.h>
#include <dxgi1_6.h>

using namespace orhi::impl::dx12;

namespace orhi
{
	template<>
	Descriptor::TDescriptor(
		Device& p_device,
		const data::TextureViewDesc& p_desc
	) : m_context{
		.device = p_device,
		.type = EDirectXDescriptorType::IMAGE_VIEW
	}
	{

	}

	template<>
	Descriptor::TDescriptor(
		Device& p_device,
		const data::SamplerDesc& p_desc
	) : m_context{
		.device = p_device,
		.type = EDirectXDescriptorType::SAMPLER
	}
	{
		
	}

	template<>
	Descriptor::~TDescriptor()
	{
		
	}
}

template class orhi::api::TDescriptor<orhi::impl::dx12::BackendTraits>;

#endif // #if defined(ORHI_COMPILE_DX12)
