/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/types/EBufferUsageFlags.h>

#include <cstdint>

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
