/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry, Jian Bang Xu
* @licence: MIT
*/

#if defined(ORHI_COMPILE_DX12)

#include <orhi/impl/dx12/CommandPool.h>

#include <orhi/debug/Assert.h>
#include <orhi/debug/Log.h>
#include <orhi/impl/dx12/detail/Types.h>
#include <orhi/impl/dx12/CommandBuffer.h>

#include <d3d12.h>
#include <dxgi1_6.h>

using namespace orhi::impl::dx12;

namespace orhi
{
	template<>
	CommandPool::TCommandPool(
		Device& p_device
	) : m_context{
		.device = p_device
	}
	{

	}

	template<>
	CommandPool::~TCommandPool()
	{
		
	}

	template<>
	std::vector<std::reference_wrapper<CommandBuffer>> CommandPool::AllocateCommandBuffers(
		uint32_t p_count,
		types::ECommandBufferLevel p_level
	)
	{
		std::vector<std::reference_wrapper<CommandBuffer>> output;
		return output;
	}
}

template class orhi::api::TCommandPool<orhi::impl::dx12::BackendTraits>;

#endif // #if defined(ORHI_COMPILE_DX12)
