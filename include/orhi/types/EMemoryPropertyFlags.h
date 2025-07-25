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
	* @brief Memory property flags enumeration for memory allocation
	* 
	* Defines the characteristics and access patterns of allocated memory,
	* including device locality, host visibility, caching behavior, and
	* special properties for different memory types and vendors.
	*/
	enum class EMemoryPropertyFlags : uint32_t
	{
		NONE = 0,											// No specific memory properties
		DEVICE_LOCAL_BIT = 0x00000001,						// Memory is located on the device (fastest for GPU access)
		HOST_VISIBLE_BIT = 0x00000002,						// Memory is visible to the host (CPU can access)
		HOST_COHERENT_BIT = 0x00000004,						// Memory is coherent between host and device
		HOST_CACHED_BIT = 0x00000008,						// Memory is cached on the host side
		LAZILY_ALLOCATED_BIT = 0x00000010,					// Memory is allocated on demand
		PROTECTED_BIT = 0x00000020,							// Memory is protected (secure)
		DEVICE_COHERENT_BIT_AMD = 0x00000040,				// AMD device coherent memory
		DEVICE_UNCACHED_BIT_AMD = 0x00000080,				// AMD device uncached memory
		RDMA_CAPABLE_BIT_NV = 0x00000100,					// NVIDIA RDMA capable memory
		ALL = ~NONE,										// All memory property flags
	};
}

ENABLE_BITMASK_OPERATORS(orhi::types::EMemoryPropertyFlags);
