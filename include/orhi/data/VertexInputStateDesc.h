/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/data/VertexAttributeDesc.h>
#include <orhi/data/VertexBindingDesc.h>

#include <span>

namespace orhi::data
{
	/**
	* Vertex input state descriptor
	*/
	struct VertexInputStateDesc
	{
		std::span<const VertexBindingDesc> vertexBindings;
		std::span<const VertexAttributeDesc> vertexAttributes;
	};
}
