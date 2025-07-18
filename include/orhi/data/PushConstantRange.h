/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/types/EShaderStageFlags.h>

namespace orhi::data
{
	/**
	* @brief Push constant range descriptor
	* 
	* Defines a range of push constants that can be updated efficiently
	* without descriptor sets. Push constants provide fast access to
	* small amounts of data from shaders.
	*/
	struct PushConstantRange
	{
		types::EShaderStageFlags stageFlags;
		uint32_t offset;
		uint32_t size;
	};
}
