/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

namespace orhi::types
{
	/**
	* Enumeration of texture filtering modes
	*/
	enum class ETextureFilteringMode : uint8_t
	{
		NEAREST,
		LINEAR,
		NEAREST_MIPMAP_NEAREST,
		LINEAR_MIPMAP_LINEAR,
		LINEAR_MIPMAP_NEAREST,
		NEAREST_MIPMAP_LINEAR
	};
}
