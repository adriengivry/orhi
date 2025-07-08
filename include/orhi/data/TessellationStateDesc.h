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
	* Tessellation state descriptor
	*/
	struct TessellationStateDesc
	{
		uint32_t patchControlPoints = 3;
	};
}
