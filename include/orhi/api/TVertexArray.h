/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/api/TVertexBuffer.h>
#include <orhi/api/TIndexBuffer.h>
#include <orhi/types/EDataType.h>
#include <orhi/types/EGraphicsBackend.h>
#include <orhi/data/VertexAttribute.h>

namespace orhi::api
{
	/**
	* Represents a vertex array, used to descript the vertex layout to the graphics backend.
	*/
	template<types::EGraphicsBackend Backend, class VertexArrayContext, class VertexBufferContext, class IndexBufferContext, class BufferContext>
	class TVertexArray final
	{
	public:
		using IndexBuffer = TIndexBuffer<Backend, IndexBufferContext, BufferContext>;
		using VertexBuffer = TVertexBuffer<Backend, VertexBufferContext, BufferContext>;

		/**
		* Creates the vertex array.
		*/
		TVertexArray();

		/**
		* Destroys the vertex array.
		*/
		~TVertexArray();

		/**
		* Returns true if the vertex array is valid (non-empty layout).
		*/
		bool IsValid() const;

		/**
		* Sets the vertex attribute layout.
		* @param p_attributes
		* @param p_vertexBuffer
		* @param p_indexBuffer
		*/
		void SetLayout(
			data::VertexAttributeLayout p_attributes,
			VertexBuffer& p_vertexBuffer,
			IndexBuffer& p_indexBuffer
		);

		/**
		* Resets the vertex attribute layout.
		*/
		void ResetLayout();

		/**
		* Binds the vertex array.
		*/
		void Bind() const;

		/**
		* Unbinds the vertex array.
		*/
		void Unbind() const;

		/**
		* Returns the vertex array ID.
		*/
		uint32_t GetID() const;

	private:
		VertexArrayContext m_context;
	};
}
