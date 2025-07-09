/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <cstdint>
#include <orhi/data/Extent3D.h>
#include <orhi/data/Offset3D.h>

namespace orhi::data
{
	/**
	*
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
