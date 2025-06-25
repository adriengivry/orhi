/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#if defined(ORHI_COMPILE_VULKAN)

#include <orhi/debug/Assert.h>
#include <orhi/impl/vk/Buffer.h>

using namespace orhi::impl::vk;

namespace orhi
{
	template<>
	Buffer::TBuffer(types::EBufferType p_type) : m_buffer{
		.type = p_type
	}
	{
	}

	template<>
	Buffer::~TBuffer()
	{
	}

	template<>
	uint64_t Buffer::Allocate(size_t p_size, types::EAccessSpecifier p_usage)
	{
		return m_buffer.allocatedBytes = p_size;
	}

	template<>
	void Buffer::Upload(const void* p_data, std::optional<data::BufferMemoryRange> p_range)
	{
		ORHI_ASSERT(IsValid(), "Trying to upload data to an invalid buffer");
		ORHI_ASSERT(!IsEmpty(), "Trying to upload data to an empty buffer");
	}

	template<>
	void Buffer::Bind(std::optional<uint32_t> p_index) const
	{
		ORHI_ASSERT(IsValid(), "Cannot bind an invalid buffer");
	}

	template<>
	void Buffer::Unbind() const
	{
		ORHI_ASSERT(IsValid(), "Cannot unbind an invalid buffer");
	}

	template<>
	bool Buffer::IsValid() const
	{
		return
			m_buffer.type != types::EBufferType::UNKNOWN &&
			m_buffer.allocatedBytes > 0;
	}

	template<>
	bool Buffer::IsEmpty() const
	{
		return GetSize() == 0;
	}

	template<>
	uint64_t Buffer::GetSize() const
	{
		ORHI_ASSERT(IsValid(), "Cannot get size of an invalid buffer");
		return m_buffer.allocatedBytes;
	}

	template<>
	uint32_t Buffer::GetID() const
	{
		ORHI_ASSERT(IsValid(), "Cannot get ID of an invalid buffer");
		return 0;
	}
}

#endif // #if defined(ORHI_COMPILE_VULKAN)
