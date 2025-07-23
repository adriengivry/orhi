/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry, Jian Bang Xu
* @licence: MIT
*/

#if defined(ORHI_COMPILE_DX12)

#include <orhi/impl/dx12/DescriptorSetLayout.h>

#include <orhi/debug/Assert.h>
#include <orhi/debug/Log.h>
#include <orhi/impl/dx12/detail/Types.h>

#include <d3d12.h>
#include <dxgi1_6.h>

using namespace orhi::impl::dx12;

namespace orhi
{
	template<>
	DescriptorSetLayout::TDescriptorSetLayout(
		Device& p_device,
		std::initializer_list<data::DescriptorBinding> p_bindings
	) : m_context{
		.device = p_device
	}
	{
	}

	template<>
	DescriptorSetLayout::~TDescriptorSetLayout()
	{
	}
}

template class orhi::api::TDescriptorSetLayout<orhi::impl::dx12::BackendTraits>;

#endif // #if defined(ORHI_COMPILE_DX12)
