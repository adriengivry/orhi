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
	* 
	*/
	struct BufferCopyDesc
	{
		uint64_t srcOffset;
		uint64_t dstOffset;
		uint64_t size;
	};
}
