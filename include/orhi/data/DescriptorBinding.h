/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/types/EDescriptorType.h>
#include <orhi/types/EShaderStageFlags.h>

namespace orhi::data
{
	/**
	* @brief Descriptor binding specification for descriptor set layouts
	* 
	* Defines a single binding point within a descriptor set layout, specifying
	* the binding number, descriptor type, and which shader stages can access
	* the descriptor at this binding point.
	*/
	struct DescriptorBinding
	{
		uint32_t binding;
		types::EDescriptorType type;
		types::EShaderStageFlags stageFlags;
	};
}
