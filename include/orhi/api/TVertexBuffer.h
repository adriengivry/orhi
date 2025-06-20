/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/api/TBuffer.h>

namespace orhi::api
{
	/**
	* Represents a vertex buffer, used to store vertex data for the graphics backend to use.
	*/
	template<types::EGraphicsBackend Backend, class VertexBufferContext, class BufferContext>
	class TVertexBuffer final : public TBuffer<Backend, BufferContext>
	{
	public:
		/**
		* Creates a vertex buffer.
		*/
		TVertexBuffer();

	private:
		VertexBufferContext m_context;
	};
}
