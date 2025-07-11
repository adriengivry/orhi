/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/data/Extent3D.h>
#include <orhi/data/Offset3D.h>

namespace orhi::data
{
	/**
	* @brief Descriptor for buffer-to-texture copy operations
	* 
	* Defines the parameters for copying image data from a buffer to a texture,
	* including buffer layout information (offset, row length, image height)
	* and texture region information (offset and extent).
	*/
	struct BufferTextureCopyDesc
	{
		uint64_t bufferOffset;
		uint32_t bufferRowLength;
		uint32_t bufferImageHeight;
		Offset3D imageOffset;
		Extent3D imageExtent;
	};
}
