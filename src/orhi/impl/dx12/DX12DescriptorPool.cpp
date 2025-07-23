/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry, Jian Bang Xu
* @licence: MIT
*/

#if defined(ORHI_COMPILE_DX12)

#include <orhi/impl/dx12/DescriptorPool.h>

#include <orhi/debug/Assert.h>
#include <orhi/debug/Log.h>
#include <orhi/impl/dx12/detail/Types.h>

#include <d3d12.h>
#include <dxgi1_6.h>

using namespace orhi::impl::dx12;

namespace orhi
{
	template<>
	DescriptorPool::TDescriptorPool(
		Device& p_device,
		const data::DescriptorPoolDesc& p_desc
	)
	{
		
	}

	template<>
	DescriptorPool::~TDescriptorPool()
	{
		
	}

	template<>
	DescriptorSet& DescriptorPool::AllocateDescriptorSet(
		const data::DescriptorSetDesc& p_desc
	)
	{
		static DescriptorSet* descriptorSet = nullptr;
		return *descriptorSet;
	}

	template<>
	void DescriptorPool::DeallocateDescriptorSet(DescriptorSet& p_descriptorSet)
	{
		
	}

	template<>
	void DescriptorPool::Reset()
	{
		
	}
}

template class orhi::api::TDescriptorPool<orhi::impl::dx12::BackendTraits>;

#endif // #if defined(ORHI_COMPILE_DX12)
