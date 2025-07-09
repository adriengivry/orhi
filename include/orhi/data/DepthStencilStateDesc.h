/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/types/ECompareOp.h>
#include <orhi/types/EStencilOp.h>

namespace orhi::data
{
	/**
	* Stencil operation state descriptor
	*/
	struct StencilOpStateDesc
	{
		types::EStencilOp failOp = types::EStencilOp::KEEP;
		types::EStencilOp passOp = types::EStencilOp::KEEP;
		types::EStencilOp depthFailOp = types::EStencilOp::KEEP;
		types::ECompareOp compareOp = types::ECompareOp::NEVER;
		uint32_t compareMask = 0;
		uint32_t writeMask = 0;
		uint32_t reference = 0;
	};

	/**
	* Depth stencil state descriptor
	*/
	struct DepthStencilStateDesc
	{
		bool depthTestEnable = false;
		bool depthWriteEnable = false;
		types::ECompareOp depthCompareOp = types::ECompareOp::LESS;
		bool depthBoundsTestEnable = false;
		bool stencilTestEnable = false;
		StencilOpStateDesc front{};
		StencilOpStateDesc back{};
		float minDepthBounds = 0.0f;
		float maxDepthBounds = 1.0f;
	};
}
