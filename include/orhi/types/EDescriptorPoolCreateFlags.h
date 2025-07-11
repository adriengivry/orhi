/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/utils/BitmaskOperators.h>

namespace orhi::types
{
	/**
	* @brief Descriptor pool creation flags enumeration
	* 
	* Defines special properties and behaviors for descriptor pools,
	* including whether individual descriptor sets can be freed,
	* support for update-after-bind operations, and host-only pools.
	*/
	enum class EDescriptorPoolCreateFlags : uint32_t
	{
		NONE = 0,
		FREE_DESCRIPTOR_SET_BIT = 0x00000001,
		UPDATE_AFTER_BIND_BIT = 0x00000002,
		HOST_ONLY_BIT_EXT = 0x00000004,
		ALLOW_OVERALLOCATION_SETS_BIT_NV = 0x00000008,
		ALLOW_OVERALLOCATION_POOLS_BIT_NV = 0x00000010,
		UPDATE_AFTER_BIND_BIT_EXT = UPDATE_AFTER_BIND_BIT,
		HOST_ONLY_BIT_VALVE = HOST_ONLY_BIT_EXT
	};
}

ENABLE_BITMASK_OPERATORS(orhi::types::EDescriptorPoolCreateFlags)
