/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/types/EDescriptorType.h>

#include <cstdint>

namespace orhi::data
{
	/**
	* Descriptor pool size specification
	*/
	struct DescriptorPoolSize
	{
		types::EDescriptorType type;
		uint32_t descriptorCount;
	};
}
