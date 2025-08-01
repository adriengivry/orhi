/**
* @project: orhi (OpenRHI)
* @author: Robert Osborne
* @licence: MIT
*/

#pragma once


#include <orhi/data/ClearValue.h>
#include <orhi/api/TBackendTraits.h>
#include <orhi/api/TFramebuffer.h>
#include <orhi/data/ViewportDesc.h>

#include <cstdint>
namespace orhi::api
{
	/**
	* @brief Information about a rendering operation
	* Gives information for BeginRendering() including the framebuffer,
	* viewport, and clear values.
	*/
	template<typename BackendTraits>
	struct RenderingInfo
	{
		uint32_t numRenderTargets;
		TFramebuffer<BackendTraits>** framebuffer;
		ViewportDesc viewport; // Viewport settings
		// TODO: Add data for depth/stencil attachment
		ColorClearValue clearColor[8]; // Up to 8 color attachments
		DepthStencilClearValue clearDepthStencil; // Single depth/stencil attachment


	};
}