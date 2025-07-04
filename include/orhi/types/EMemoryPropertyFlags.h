/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <cstdint>
#include <orhi/utils/BitmaskOperators.h>

namespace orhi::types
{
	/**
	* 
	*/
	enum class EMemoryPropertyFlags : uint32_t
	{
		NONE = 0,
		DEVICE_LOCAL_BIT = 0x00000001,
		HOST_VISIBLE_BIT = 0x00000002,
		HOST_COHERENT_BIT = 0x00000004,
		HOST_CACHED_BIT = 0x00000008,
		LAZILY_ALLOCATED_BIT = 0x00000010,
		PROTECTED_BIT = 0x00000020,
		DEVICE_COHERENT_BIT_AMD = 0x00000040,
		DEVICE_UNCACHED_BIT_AMD = 0x00000080,
		RDMA_CAPABLE_BIT_NV = 0x00000100,
		ALL = ~NONE,
	};
}

ENABLE_BITMASK_OPERATORS(orhi::types::EMemoryPropertyFlags);
