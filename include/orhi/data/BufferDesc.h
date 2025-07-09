/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <cstdint>
#include <orhi/types/EBufferUsageFlags.h>

namespace orhi::data
{
	/**
	* 
	*/
	struct BufferDesc
	{
		uint64_t size;
		types::EBufferUsageFlags usage;
	};
}
