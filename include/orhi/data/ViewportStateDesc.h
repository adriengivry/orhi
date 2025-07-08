/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/data/ViewportDesc.h>
#include <orhi/data/Rect2D.h>
#include <span>

namespace orhi::data
{
	/**
	* Viewport state descriptor
	*/
	struct ViewportStateDesc
	{
		std::span<const ViewportDesc> viewports;
		std::span<const Rect2D> scissors;
	};
}
