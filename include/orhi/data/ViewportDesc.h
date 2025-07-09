/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

namespace orhi::data
{
	/**
	*
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
