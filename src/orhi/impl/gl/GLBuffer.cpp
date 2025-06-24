/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#if defined(ORHI_COMPILE_OPENGL)

#include <orhi/debug/Assert.h>
#include <orhi/impl/gl/details/glad/glad.h>
#include <orhi/impl/gl/details/Types.h>
#include <orhi/impl/gl/Buffer.h>

using namespace orhi::impl::gl;

namespace orhi
{
	template<>
	Buffer::TBuffer(types::EBufferType p_type) : m_buffer{
		.type = p_type
	}
	{
		glCreateBuffers(1, &m_buffer.id);
	}

	template<>
	Buffer::~TBuffer()
	{
		glDeleteBuffers(1, &m_buffer.id);
	}

	template<>
	uint64_t Buffer::Allocate(uint64_t p_size, types::EAccessSpecifier p_usage)
	{
		ORHI_ASSERT(IsValid(), "Cannot allocate memory for an invalid buffer");
		glNamedBufferData(m_buffer.id, p_size, nullptr, utils::EnumToValue<GLenum>(p_usage));
		return m_buffer.allocatedBytes = p_size;
	}

	template<>
	void Buffer::Upload(const void* p_data, std::optional<data::BufferMemoryRange> p_range)
	{
		ORHI_ASSERT(IsValid(), "Trying to upload data to an invalid buffer");
		ORHI_ASSERT(!IsEmpty(), "Trying to upload data to an empty buffer");

		glNamedBufferSubData(
			m_buffer.id,
			p_range ? p_range->offset : 0,
			p_range ? p_range->size : m_buffer.allocatedBytes,
			p_data
		);
	}

	template<>
	void Buffer::Bind(std::optional<uint32_t> p_index) const
	{
		ORHI_ASSERT(IsValid(), "Cannot bind an invalid buffer");

		if (p_index.has_value())
		{
			glBindBufferBase(utils::EnumToValue<GLenum>(m_buffer.type), p_index.value(), m_buffer.id);
		}
		else
		{
			glBindBuffer(utils::EnumToValue<GLenum>(m_buffer.type), m_buffer.id);
		}
	}

	template<>
	void Buffer::Unbind() const
	{
		ORHI_ASSERT(IsValid(), "Cannot unbind an invalid buffer");
		glBindBuffer(utils::EnumToValue<GLenum>(m_buffer.type), 0);
	}

	template<>
	bool Buffer::IsValid() const
	{
		return
			m_buffer.id != 0 &&
			m_buffer.type != types::EBufferType::UNKNOWN;
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
		return m_buffer.id;
	}
}

#endif // #if defined(ORHI_COMPILE_OPENGL)
