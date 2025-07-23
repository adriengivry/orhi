/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/utils/BitmaskOperators.h>

#include <cstdint>

namespace orhi::types
{
	/**
	* @brief Texture usage flags enumeration for texture creation
	* 
	* Defines how a texture will be used during its lifetime, including
	* sampling, storage, attachment, and transfer operations. Multiple
	* usage flags can be combined to support different access patterns.
	*/
	enum class ETextureUsageFlags : uint32_t
	{
		NONE = 0,
		TRANSFER_SRC_BIT = 1 << 0,
		TRANSFER_DST_BIT = 1 << 1,
		SAMPLED_BIT = 1 << 2,
		STORAGE_BIT = 1 << 3,
		COLOR_ATTACHMENT_BIT = 1 << 4,
		DEPTH_STENCIL_ATTACHMENT_BIT = 1 << 5,
		TRANSIENT_ATTACHMENT_BIT = 1 << 6,
		INPUT_ATTACHMENT_BIT = 1 << 7,
		ALL = ~NONE,
	};
}

ENABLE_BITMASK_OPERATORS(orhi::types::ETextureUsageFlags);
