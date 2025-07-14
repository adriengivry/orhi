/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <cstdint>

namespace orhi::types
{
	/**
	* @brief Enum representing different types of attachments in a render pass
	*/
	enum class EAttachmentType : uint8_t
	{
		COLOR,
		DEPTH_STENCIL
	};
}
