/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry, Jian Bang Xu
* @licence: MIT
*/

#if defined(ORHI_COMPILE_DX12)

#include <orhi/impl/dx12/DescriptorSet.h>

#include <orhi/debug/Assert.h>
#include <orhi/debug/Log.h>
#include <orhi/impl/dx12/detail/Types.h>

#include <d3d12.h>
#include <dxgi1_6.h>

using namespace orhi::impl::dx12;

namespace orhi
{
	template<>
	DescriptorSet::TDescriptorSet(
		Device& p_device,
		impl::common::NativeHandle p_handle
	) :
		BackendObject(p_handle),
		m_context {
			.device = p_device
		}
	{
		
	}

	template<>
	DescriptorSet::~TDescriptorSet()
	{
		
	}

	template<>
	void DescriptorSet::Write(
		const std::unordered_map<uint32_t, data::DescriptorWriteDesc<BackendTraits>>& p_writeDescs
	)
	{
		
	}
}

template class orhi::api::TDescriptorSet<orhi::impl::dx12::BackendTraits>;

#endif // #if defined(ORHI_COMPILE_DX12)
