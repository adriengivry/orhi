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
	* @brief Shader stage flags enumeration for resource binding and access
	* 
	* Defines which shader stages can access specific resources such as
	* descriptors, push constants, and pipeline barriers. Multiple stages
	* can be combined to specify resource visibility across pipeline stages.
	*/
	enum class EShaderStageFlags : uint32_t
	{
		NONE = 0,
		VERTEX_BIT = 0x00000001,
		TESSELLATION_CONTROL_BIT = 0x00000002,
		TESSELLATION_EVALUATION_BIT = 0x00000004,
		GEOMETRY_BIT = 0x00000008,
		FRAGMENT_BIT = 0x00000010,
		COMPUTE_BIT = 0x00000020,
		ALL_GRAPHICS = 0x0000001F,
		RAYGEN_BIT_KHR = 0x00000100,
		ANY_HIT_BIT_KHR = 0x00000200,
		CLOSEST_HIT_BIT_KHR = 0x00000400,
		MISS_BIT_KHR = 0x00000800,
		INTERSECTION_BIT_KHR = 0x00001000,
		CALLABLE_BIT_KHR = 0x00002000,
		TASK_BIT_EXT = 0x00000040,
		MESH_BIT_EXT = 0x00000080,
		SUBPASS_SHADING_BIT_HUAWEI = 0x00004000,
		CLUSTER_CULLING_BIT_HUAWEI = 0x00080000,
		RAYGEN_BIT_NV = RAYGEN_BIT_KHR,
		ANY_HIT_BIT_NV = ANY_HIT_BIT_KHR,
		CLOSEST_HIT_BIT_NV = CLOSEST_HIT_BIT_KHR,
		MISS_BIT_NV = MISS_BIT_KHR,
		INTERSECTION_BIT_NV = INTERSECTION_BIT_KHR,
		CALLABLE_BIT_NV = CALLABLE_BIT_KHR,
		TASK_BIT_NV = TASK_BIT_EXT,
		MESH_BIT_NV = MESH_BIT_EXT,
		ALL = ~NONE,
	};
}

ENABLE_BITMASK_OPERATORS(orhi::types::EShaderStageFlags);
