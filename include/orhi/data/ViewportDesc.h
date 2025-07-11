/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

namespace orhi::data
{
	/**
	* @brief Viewport descriptor defining the viewport transformation
	* 
	* Specifies the viewport transformation parameters including position,
	* size, and depth range. Controls how normalized device coordinates
	* are mapped to screen coordinates during rendering.
	*/
	struct ViewportDesc
	{
		float x;
		float y;
		float width;
		float height;
		float minDepth;
		float maxDepth;
	};
}
