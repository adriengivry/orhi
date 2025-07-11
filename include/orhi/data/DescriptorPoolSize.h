/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/types/EDescriptorType.h>

namespace orhi::data
{
	/**
	* @brief Descriptor pool size specification
	* 
	* Specifies the type and count of descriptors available in a descriptor pool.
	* Used to define how many descriptors of each type can be allocated from
	* the pool when creating descriptor sets.
	*/
	struct DescriptorPoolSize
	{
		types::EDescriptorType type;
		uint32_t descriptorCount;
	};
}
