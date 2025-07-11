/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <cstdint>

namespace orhi::data
{
	/**
	* @brief Vertex buffer binding descriptor for vertex input state
	* 
	* Defines how a vertex buffer is bound to the graphics pipeline, including
	* the binding index and the stride (size in bytes) between consecutive
	* vertex elements in the buffer.
	*/
	struct VertexBindingDesc
	{
		uint32_t binding;
		uint32_t stride;
	};
}
