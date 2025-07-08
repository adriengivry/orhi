/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/data/DescriptorPoolSize.h>
#include <orhi/types/EDescriptorPoolCreateFlags.h>
#include <vector>
#include <cstdint>

namespace orhi::data
{
	/**
	* Descriptor pool creation description
	*/
	struct DescriptorPoolDesc
	{
		types::EDescriptorPoolCreateFlags flags = types::EDescriptorPoolCreateFlags::NONE;
		uint32_t maxSets;
		std::vector<DescriptorPoolSize> poolSizes;
	};
}
