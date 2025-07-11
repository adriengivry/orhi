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
	* @brief Stencil operation state descriptor
	* 
	* Defines the stencil operations to perform when stencil tests fail or pass,
	* including the comparison operation and reference values for stencil testing.
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
	* @brief Depth and stencil state descriptor for graphics pipelines
	* 
	* Defines the depth and stencil testing configuration for a graphics pipeline,
	* including depth comparison operations, stencil operations, and depth bounds testing.
	* Controls how fragments are tested against existing depth and stencil values.
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
