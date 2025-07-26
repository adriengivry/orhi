/**
* @project: orhi (OpenRHI)
* @author: Jian Bang Xu
* @licence: MIT
*/

#pragma once

#include <cstdint>

namespace orhi::types
{
	/**
	* @brief Buffer view type enumeration for DirectX descriptor specification
	* 
	* Defines the type of buffer view descriptor, determining how buffer resources
	* are interpreted and accessed by shaders during rendering operations.
	*/
	enum class EBufferViewType : uint8_t
	{
		CONSTANT_BUFFER_VIEW,
		SHADER_RESOURCE_VIEW,
		UNORDERED_ACCESS_VIEW,
	};
}