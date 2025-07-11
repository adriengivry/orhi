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
	* @brief Descriptor for buffer-to-buffer copy operations
	* 
	* Defines the parameters for copying data between two buffers, including
	* source and destination offsets and the number of bytes to copy.
	*/
	struct BufferCopyDesc
	{
		uint64_t srcOffset;
		uint64_t dstOffset;
		uint64_t size;
	};
}
