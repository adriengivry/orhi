/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/api/TBuffer.h>
#include <orhi/types/EGraphicsBackend.h>

namespace orhi::api
{
	/**
	* Represents a shader storage buffer, used to store data of variable size that can be accessed by shaders.
	*/
	template<types::EGraphicsBackend Backend, class ShaderStorageBufferContext, class BufferContext>
	class TShaderStorageBuffer : public TBuffer<Backend, BufferContext>
	{
	public:
		/**
		* Creates a shader storage buffer.
		*/
		TShaderStorageBuffer();

	private:
		ShaderStorageBufferContext m_context;
	};
}
