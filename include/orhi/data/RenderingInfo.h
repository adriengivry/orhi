/**
* @project: orhi (OpenRHI)
* @author: Robert Osborne
* @licence: MIT
*/

#pragma once

#include <orhi/api/TFramebuffer.h>
#include <orhi/data/ClearValue.h>
#include <orhi/math/Extent2D.h>

#include <initializer_list>

namespace orhi::api
{
	/**
	* @brief Information about a rendering operation
	*
	* Supplies the attachment set, render area, and clear values for
	* BeginRendering().
	*/
	template<typename BackendTraits>
	struct RenderingInfo
	{
		TFramebuffer<BackendTraits>& framebuffer;
		math::Extent2D extent;
		// Indexed by framebuffer attachment order. Resolve entries are ignored.
		// Missing values leave the corresponding contents undefined on load.
		std::initializer_list<data::ClearValue> clearValues = {};
	};
}
