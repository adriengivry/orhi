/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <string>

#include <orhi/api/TBuffer.h>

namespace orhi::Resources { class Shader; }

namespace orhi::api
{
	/**
	* Represents a uniform buffer, used to store uniform data that can be accessed by shaders
	*/
	template<types::EGraphicsBackend Backend, class UniformBufferContext, class BufferContext>
	class TUniformBuffer : public TBuffer<Backend, BufferContext>
	{
	public:
		/**
		* Creates a UniformBuffer
		*/
		TUniformBuffer();

	private:
		UniformBufferContext m_context;
	};
}
