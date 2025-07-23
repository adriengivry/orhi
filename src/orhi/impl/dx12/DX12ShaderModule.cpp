/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry, Jian Bang Xu
* @licence: MIT
*/

#if defined(ORHI_COMPILE_DX12)

#include <orhi/impl/dx12/ShaderModule.h>

#include <orhi/debug/Assert.h>
#include <orhi/debug/Log.h>

#include <d3d12.h>
#include <dxgi1_6.h>

using namespace orhi::impl::dx12;

namespace orhi
{
	template<>
	ShaderModule::TShaderModule(
		Device& p_device,
		const std::span<const std::byte> p_source
	) : m_context{
		.device = p_device
	}
	{
		
	}

	template<>
	ShaderModule::~TShaderModule()
	{
	}
}

template class orhi::api::TShaderModule<orhi::impl::dx12::BackendTraits>;

#endif // #if defined(ORHI_COMPILE_DX12)
