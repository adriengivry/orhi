/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry, Jian Bang Xu
* @licence: MIT
*/

#if defined(ORHI_COMPILE_DX12)

#include <orhi/impl/dx12/Buffer.h>

#include <orhi/debug/Assert.h>
#include <orhi/debug/Log.h>
#include <orhi/impl/dx12/detail/MemoryUtils.h>
#include <orhi/impl/dx12/detail/Types.h>

#include <d3d12.h>
#include <dxgi1_6.h>

using namespace orhi::impl::dx12;

namespace orhi
{
	template<>
	Buffer::TBuffer(
		Device& p_device,
		const data::BufferDesc& p_desc
	) : m_context{
		.device = p_device,
		.memory = nullptr,
		.allocatedBytes = 0ULL
	}
	{
		// Constructor now only stores the buffer description
		// Actual GPU memory allocation is deferred to Allocate()
	}

	template<>
	Buffer::~TBuffer()
	{
		if (IsAllocated())
		{
			Deallocate();
		}
	}

	template<>
	bool Buffer::IsAllocated() const
	{
		return m_context.memory != nullptr && m_context.allocatedBytes > 0;
	}

	template<>
	void Buffer::Allocate(types::EMemoryPropertyFlags p_properties)
	{
	}

	template<>
	void Buffer::Deallocate()
	{
	}

	template<>
	void Buffer::Upload(
		const void* p_data,
		std::optional<data::MemoryRange> p_memoryRange
	)
	{
	}

	template<>
	uint64_t Buffer::GetAllocatedBytes() const
	{
		return m_context.allocatedBytes;
	}
}

template class orhi::api::TBuffer<orhi::impl::dx12::BackendTraits>;

#endif // #if defined(ORHI_COMPILE_DX12)
