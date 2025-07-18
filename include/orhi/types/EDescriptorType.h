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
	* @brief Descriptor types enumeration for descriptor set bindings
	* 
	* Defines the types of resources that can be bound to descriptor sets,
	* including textures, samplers, buffers, and specialized descriptors.
	* Each type determines how the resource is accessed by shaders.
	*/
	enum class EDescriptorType
	{
		SAMPLER = 0,
		COMBINED_IMAGE_SAMPLER = 1,
		SAMPLED_IMAGE = 2,
		STORAGE_IMAGE = 3,
		UNIFORM_TEXEL_BUFFER = 4,
		STORAGE_TEXEL_BUFFER = 5,
		UNIFORM_BUFFER = 6,
		STORAGE_BUFFER = 7,
		UNIFORM_BUFFER_DYNAMIC = 8,
		STORAGE_BUFFER_DYNAMIC = 9,
		INPUT_ATTACHMENT = 10,
		INLINE_UNIFORM_BLOCK = 1000138000,
		ACCELERATION_STRUCTURE_KHR = 1000150000,
		ACCELERATION_STRUCTURE_NV = 1000165000,
		SAMPLE_WEIGHT_IMAGE_QCOM = 1000440000,
		BLOCK_MATCH_IMAGE_QCOM = 1000440001,
		MUTABLE_EXT = 1000351000,
		PARTITIONED_ACCELERATION_STRUCTURE_NV = 1000570000,
		INLINE_UNIFORM_BLOCK_EXT = INLINE_UNIFORM_BLOCK,
		MUTABLE_VALVE = MUTABLE_EXT,
	};
}
