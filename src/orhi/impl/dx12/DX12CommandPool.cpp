/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry, Jian Bang Xu, Robert Osborne
* @licence: MIT
*/

#if defined(ORHI_COMPILE_DX12)

#include <orhi/impl/dx12/CommandPool.h>

#include <orhi/debug/Assert.h>
#include <orhi/debug/Log.h>
#include <orhi/impl/dx12/detail/Types.h>
#include <orhi/impl/dx12/CommandBuffer.h>

#include <d3d12.h>

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
		auto device = p_device.GetNativeHandle().As<ID3D12Device*>();
		ORHI_ASSERT(device, "Device must have a valid native handle");

		HRESULT hr = device->CreateCommandAllocator(
			D3D12_COMMAND_LIST_TYPE_DIRECT, // Command list type
			IID_PPV_ARGS(&m_context.commandAllocator)
		);
		ORHI_ASSERT(SUCCEEDED(hr), "Failed to create command allocator");
		m_handle = m_context.commandAllocator.Get();

	}

	template<>
	CommandPool::~TCommandPool()
	{
		
	}

	// TODO: create way to return only one command buffer
	// TODO: maybe should be the only way to allocate command buffers?

	template<>
	std::vector<std::reference_wrapper<CommandBuffer>> CommandPool::AllocateCommandBuffers(
		uint32_t p_count,
		types::ECommandBufferLevel p_level
	)
	{
		std::vector<std::reference_wrapper<CommandBuffer>> output;

		for (uint32_t i = 0; i < p_count; ++i)
		{
			CommandBuffer commandBuffer(m_context.device, *this);

		}


		return output;
	}
}

template class orhi::api::TCommandPool<orhi::impl::dx12::BackendTraits>;

#endif // #if defined(ORHI_COMPILE_DX12)
