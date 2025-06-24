/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#if defined(ORHI_COMPILE_OPENGL)

#include <orhi/debug/Assert.h>
#include <orhi/impl/gl/details/glad/glad.h>
#include <orhi/impl/gl/details/Types.h>
#include <orhi/impl/gl/VertexArray.h>

using namespace orhi::impl::gl;

namespace
{
	uint32_t GetDataTypeSizeInBytes(orhi::types::EDataType p_type)
	{
		switch (p_type)
		{
		case orhi::types::EDataType::BYTE: return sizeof(GLbyte);
		case orhi::types::EDataType::UNSIGNED_BYTE: return sizeof(GLubyte);
		case orhi::types::EDataType::SHORT: return sizeof(GLshort);
		case orhi::types::EDataType::UNSIGNED_SHORT: return sizeof(GLushort);
		case orhi::types::EDataType::INT: return sizeof(GLint);
		case orhi::types::EDataType::UNSIGNED_INT: return sizeof(GLuint);
		case orhi::types::EDataType::FLOAT: return sizeof(GLfloat);
		case orhi::types::EDataType::DOUBLE: return sizeof(GLdouble);
		default: return 0;
		}
	}

	uint32_t CalculateTotalVertexSize(std::span<const orhi::data::VertexAttribute> p_attributes)
	{
		uint32_t result = 0;

		for (const auto& attribute : p_attributes)
		{
			result += GetDataTypeSizeInBytes(attribute.type) * attribute.count;
		}

		return result;
	}
}

namespace orhi
{
	template<>
	VertexArray::TVertexArray()
	{
		glCreateVertexArrays(1, &m_context.id);
	}

	template<>
	VertexArray::~TVertexArray()
	{
		glDeleteVertexArrays(1, &m_context.id);
	}

	template<>
	bool VertexArray::IsValid() const
	{
		return m_context.attributeCount > 0;
	}

	template<>
	void VertexArray::SetLayout(
		data::VertexAttributeLayout p_attributes,
		VertexBuffer& p_vertexBuffer,
		IndexBuffer& p_indexBuffer
	)
	{
		ORHI_ASSERT(!IsValid(), "Vertex array layout already set");

		Bind();
		p_indexBuffer.Bind();
		p_vertexBuffer.Bind();

		uint32_t attributeIndex = 0;

		const uint32_t totalSize = CalculateTotalVertexSize(p_attributes);
		intptr_t currentOffset = 0;

		for (const auto& attribute : p_attributes)
		{
			ORHI_ASSERT(attribute.count >= 1 && attribute.count <= 4, "Attribute count must be between 1 and 4");

			glEnableVertexAttribArray(attributeIndex);

			glVertexAttribPointer(
				static_cast<GLuint>(attributeIndex),
				static_cast<GLint>(attribute.count),
				utils::EnumToValue<GLenum>(attribute.type),
				static_cast<GLboolean>(attribute.normalized),
				static_cast<GLsizei>(totalSize),
				reinterpret_cast<const GLvoid*>(currentOffset)
			);

			const uint64_t typeSize = GetDataTypeSizeInBytes(attribute.type);
			const uint64_t attributeSize = typeSize * attribute.count;
			currentOffset += attributeSize;
			++attributeIndex;
			++m_context.attributeCount;
		}

		Unbind();
		p_indexBuffer.Unbind();
		p_vertexBuffer.Unbind();
	}

	template<>
	void VertexArray::ResetLayout()
	{
		ORHI_ASSERT(IsValid(), "Vertex array layout not already set");

		Bind();
		for (uint32_t i = 0; i < m_context.attributeCount; ++i)
		{
			glDisableVertexAttribArray(i);
		}
		m_context.attributeCount = 0;
		Unbind();
	}

	template<>
	void VertexArray::Bind() const
	{
		glBindVertexArray(m_context.id);
	}

	template<>
	void VertexArray::Unbind() const
	{
		glBindVertexArray(0);
	}

	template<>
	uint32_t VertexArray::GetID() const
	{
		return m_context.id;
	}
}

#endif // #if defined(ORHI_COMPILE_OPENGL)
