/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <cstdint>
#include <orhi/types/EFormat.h>

namespace orhi::data
{
	/**
	*
	*/
	struct VertexAttributeDesc
	{
		uint32_t binding;
		uint32_t location;
		uint32_t offset;
		types::EFormat format;
	};
}
