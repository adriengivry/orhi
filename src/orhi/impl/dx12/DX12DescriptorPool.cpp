/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry, Jian Bang Xu
* @licence: MIT
*/

#if defined(ORHI_COMPILE_DX12)

#include <orhi/impl/dx12/DescriptorPool.h>

#include <orhi/debug/Assert.h>
#include <orhi/debug/Log.h>
#include <orhi/impl/dx12/DescriptorSetLayout.h>
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
	) : m_context{
		.device = p_device,
	}
	{
		
	}

	template<>
	DescriptorPool::~TDescriptorPool()
	{
		
	}

	template<>
	std::vector<std::reference_wrapper<DescriptorSet>> DescriptorPool::AllocateDescriptorSets(
		const DescriptorSetLayout& p_layout,
		uint32_t p_count
	)
	{
		std::vector<std::reference_wrapper<DescriptorSet>> output;
		return output;
	}
}

template class orhi::api::TDescriptorPool<orhi::impl::dx12::BackendTraits>;

#endif // #if defined(ORHI_COMPILE_DX12)
