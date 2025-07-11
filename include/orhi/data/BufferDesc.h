/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/types/EBufferUsageFlags.h>

namespace orhi::data
{
	/**
	* @brief Descriptor for buffer creation
	* 
	* Specifies the properties of a buffer to be created, including its size
	* and usage flags that determine how the buffer can be used (vertex data,
	* index data, uniform data, etc.).
	*/
	struct BufferDesc
	{
		uint64_t size;
		types::EBufferUsageFlags usage;
	};
}
