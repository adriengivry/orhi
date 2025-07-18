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
	* @brief Dynamic state enumeration for graphics pipeline
	* 
	* Defines the pipeline state that can be changed dynamically during
	* command buffer recording without creating a new pipeline. Allows
	* for efficient modification of rendering parameters at runtime.
	*/
	enum class EDynamicState : uint32_t
	{
		VIEWPORT = 0,
		SCISSOR = 1,
		LINE_WIDTH = 2,
		DEPTH_BIAS = 3,
		BLEND_CONSTANTS = 4,
		DEPTH_BOUNDS = 5,
		STENCIL_COMPARE_MASK = 6,
		STENCIL_WRITE_MASK = 7,
		STENCIL_REFERENCE = 8,
		CULL_MODE = 1000267000,
		FRONT_FACE = 1000267001,
		PRIMITIVE_TOPOLOGY = 1000267002,
		VIEWPORT_WITH_COUNT = 1000267003,
		SCISSOR_WITH_COUNT = 1000267004,
		VERTEX_INPUT_BINDING_STRIDE = 1000267005,
		DEPTH_TEST_ENABLE = 1000267006,
		DEPTH_WRITE_ENABLE = 1000267007,
		DEPTH_COMPARE_OP = 1000267008,
		DEPTH_BOUNDS_TEST_ENABLE = 1000267009,
		STENCIL_TEST_ENABLE = 1000267010,
		STENCIL_OP = 1000267011,
		RASTERIZER_DISCARD_ENABLE = 1000377001,
		DEPTH_BIAS_ENABLE = 1000377002,
		PRIMITIVE_RESTART_ENABLE = 1000377004,
	};
}
