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
	* @brief Vertex input state descriptor for graphics pipelines
	* 
	* Defines the complete vertex input configuration including vertex buffer
	* bindings and vertex attribute descriptions. Specifies how vertex data
	* is organized and interpreted by the vertex shader.
	*/
	struct VertexInputStateDesc
	{
		std::span<const VertexBindingDesc> vertexBindings;
		std::span<const VertexAttributeDesc> vertexAttributes;
	};
}
