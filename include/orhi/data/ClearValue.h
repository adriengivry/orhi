/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/math/Vec2.h>
#include <orhi/math/Vec4.h>

#include <variant>

namespace orhi::data
{
	using ColorClearValue = math::Vec4f;

	/**
	* @brief A structure representing a depth-stencil clear value
	*/
	struct DepthStencilClearValue
	{
		float depth = 1.0f; // Default depth value
		uint32_t stencil = 0; // Default stencil value
	};

	/**
	* @brief A union type representing different clear values for attachments
	*/
	using ClearValue = std::variant<
		ColorClearValue,
		DepthStencilClearValue
	>;
}
