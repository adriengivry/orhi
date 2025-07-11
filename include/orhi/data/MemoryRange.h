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
	* @brief Represents a contiguous range of memory
	* 
	* Defines a memory region with an offset and size, commonly used for
	* specifying portions of buffers or textures for upload, download,
	* or copy operations.
	*/
	struct MemoryRange
	{
		uint64_t offset;
		uint64_t size;
	};
}
