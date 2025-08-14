/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/data/DescriptorPoolSize.h>
#include <orhi/types/EDescriptorPoolCreateFlags.h>

#include <cstdint>
#include <vector>

namespace orhi::data
{
	/**
	* @brief Descriptor pool creation descriptor
	* 
	* Defines the configuration for creating a descriptor pool, including
	* creation flags, maximum number of descriptor sets and constants, and the types
	* and counts of descriptors that can be allocated from the pool.
	*/
	struct DescriptorPoolDesc
	{
		types::EDescriptorPoolCreateFlags flags = types::EDescriptorPoolCreateFlags::NONE;
		uint16_t maxConstants;
		uint16_t maxSets;
		std::vector<DescriptorPoolSize> poolSizes;
	};
}
