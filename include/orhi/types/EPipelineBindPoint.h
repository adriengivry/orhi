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
	*
	*/
	enum class EPipelineBindPoint
	{
		GRAPHICS = 0,
		COMPUTE = 1,
		RAY_TRACING_KHR = 1000165000,
		SUBPASS_SHADING_HUAWEI = 1000369003,
		RAY_TRACING_NV = RAY_TRACING_KHR,
	};
}
