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
	* Represents an index buffer, used to store index data for the graphics backend to use.
	*/
	template<types::EGraphicsBackend Backend, class IndexBufferContext, class BufferContext>
	class TIndexBuffer : public TBuffer<Backend, BufferContext>
	{
	public:
		/**
		* Creates an index buffer.
		*/
		TIndexBuffer();

	private:
		IndexBufferContext m_context;
	};
}
