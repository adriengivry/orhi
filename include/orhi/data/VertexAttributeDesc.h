/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/types/EFormat.h>

#include <cstdint>

namespace orhi::data
{
	/**
	* @brief Vertex attribute descriptor for vertex input state
	* 
	* Defines a single vertex attribute including its binding point, shader location,
	* offset within the vertex structure, and data format. Used to describe how
	* vertex data is laid out and accessed by vertex shaders.
	*/
	struct VertexAttributeDesc
	{
		uint32_t binding;
		uint32_t location;
		uint32_t offset;
		types::EFormat format;
	};
}
