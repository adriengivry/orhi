/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry, Jian Bang Xu
* @licence: MIT
*/

#if defined(ORHI_COMPILE_DX12)

#include <orhi/impl/dx12/PipelineLayout.h>

#include <orhi/debug/Assert.h>
#include <orhi/debug/Log.h>
#include <orhi/impl/dx12/detail/Types.h>

#include <d3d12.h>
#include <dxgi1_6.h>

using namespace orhi::impl::dx12;

namespace orhi
{
	template<>
	PipelineLayout::TPipelineLayout(
		Device& p_device,
		const data::PipelineLayoutDesc<BackendTraits>& p_desc
	) : m_context{
		.device = p_device
	}
	{
		
	}

	template<>
	PipelineLayout::~TPipelineLayout()
	{
		
	}
}

template class orhi::api::TPipelineLayout<orhi::impl::dx12::BackendTraits>;

#endif // #if defined(ORHI_COMPILE_DX12)
