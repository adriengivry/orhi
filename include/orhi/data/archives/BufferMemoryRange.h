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
	* Struct representing a range of memory in a buffer.
	*/
	struct BufferMemoryRange
	{
		uint64_t offset;
		uint64_t size;
	};
}
