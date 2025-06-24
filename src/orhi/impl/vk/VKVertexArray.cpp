/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#if defined(ORHI_COMPILE_VULKAN)

#include <orhi/debug/Assert.h>
#include <orhi/impl/vk/VertexArray.h>

using namespace orhi::impl::vk;

namespace orhi
{
	template<>
	VertexArray::TVertexArray()
	{
	}

	template<>
	VertexArray::~TVertexArray()
	{
	}

	template<>
	void VertexArray::Bind() const
	{
	}

	template<>
	void VertexArray::Unbind() const
	{
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

		for (const auto& attribute : p_attributes)
		{
			ORHI_ASSERT(attribute.count >= 1 && attribute.count <= 4, "Attribute count must be between 1 and 4");
			++m_context.attributeCount;
		}
	}

	template<>
	void VertexArray::ResetLayout()
	{
		ORHI_ASSERT(IsValid(), "Vertex array layout not already set");
		m_context.attributeCount = 0;
	}

	template<>
	uint32_t VertexArray::GetID() const
	{
		return 0;
	}
}

#endif // #if defined(ORHI_COMPILE_VULKAN)
