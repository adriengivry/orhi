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
	* @brief Tessellation state descriptor for graphics pipelines
	* 
	* Defines the tessellation configuration, primarily the number of control points
	* per patch for tessellation operations. Used when tessellation shaders are
	* enabled in the graphics pipeline.
	*/
	struct TessellationStateDesc
	{
		uint32_t patchControlPoints = 3;
	};
}
