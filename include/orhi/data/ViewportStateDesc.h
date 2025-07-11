/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/data/ViewportDesc.h>
#include <orhi/math/Rect2D.h>

#include <span>

namespace orhi::data
{
	/**
	* @brief Viewport state descriptor for graphics pipelines
	* 
	* Defines the viewport and scissor test configuration for a graphics pipeline,
	* including arrays of viewport and scissor rectangle descriptors. Supports
	* multiple viewports for advanced rendering techniques.
	*/
	struct ViewportStateDesc
	{
		std::span<const ViewportDesc> viewports;
		std::span<const math::Rect2D> scissors;
	};
}
