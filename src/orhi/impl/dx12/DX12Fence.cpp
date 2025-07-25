/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry, Jian Bang Xu
* @licence: MIT
*/

#if defined(ORHI_COMPILE_DX12)

#include <orhi/impl/dx12/Fence.h>

#include <orhi/debug/Assert.h>
#include <orhi/debug/Log.h>
#include <orhi/impl/dx12/detail/Types.h>

#include <d3d12.h>
#include <dxgi1_6.h>

using namespace orhi::impl::dx12;

namespace orhi
{
	template<>
	Fence::TFence(Device& p_device, bool p_createSignaled) :
		m_context{
			.device = p_device
		}
	{
		
	}

	template<>
	Fence::~TFence()
	{
		
	}

	template<>
	void Fence::Wait(std::optional<uint64_t> p_timeout)
	{
		
	}

	template<>
	void Fence::Reset()
	{
		
	}
}

template class orhi::api::TFence<orhi::impl::dx12::BackendTraits>;

#endif // #if defined(ORHI_COMPILE_DX12)
