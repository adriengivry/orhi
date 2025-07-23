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

#include <d3d12.h>
#include <dxgi1_6.h>

using namespace orhi::impl::dx12;

namespace orhi
{
	template<>
	CommandPool::TCommandPool(
		Device& p_device,
		const data::CommandPoolDesc& p_desc
	)
	{
		
	}

	template<>
	CommandPool::~TCommandPool()
	{
		
	}

	template<>
	CommandBuffer& CommandPool::AllocateCommandBuffer(
		types::ECommandBufferLevel p_level
	)
	{
		static CommandBuffer* commandBuffer = nullptr;
		return *commandBuffer;
	}

	template<>
	void CommandPool::DeallocateCommandBuffer(CommandBuffer& p_commandBuffer)
	{
		
	}

	template<>
	void CommandPool::Reset()
	{
		
	}
}

template class orhi::api::TCommandPool<orhi::impl::dx12::BackendTraits>;

#endif // #if defined(ORHI_COMPILE_DX12)
