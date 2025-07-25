/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <cstdint>

namespace orhi::types
{
	/**
	* @brief Pipeline bind point enumeration for descriptor binding
	* 
	* Defines the different pipeline stages where descriptor sets and
	* pipelines can be bound, determining how resources are accessed
	* by different types of rendering operations.
	*/
	enum class EPipelineBindPoint : uint32_t
	{
		GRAPHICS = 0,
		COMPUTE = 1,
		RAY_TRACING_KHR = 1000165000,
		SUBPASS_SHADING_HUAWEI = 1000369003,
		RAY_TRACING_NV = RAY_TRACING_KHR,
	};
}
