/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <cstdint>
#include <orhi/types/EDescriptorType.h>
#include <orhi/types/EShaderStageFlags.h>

namespace orhi::data
{
	/**
	* 
	*/
	struct DescriptorBinding
	{
		uint32_t binding;
		types::EDescriptorType type;
		types::EShaderStageFlags stageFlags;
	};
}
