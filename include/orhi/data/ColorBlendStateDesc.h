/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/types/EBlendFactor.h>
#include <orhi/types/EBlendOp.h>
#include <orhi/types/EColorComponentFlags.h>
#include <orhi/types/ELogicOp.h>

#include <array>
#include <span>

namespace orhi::data
{
	/**
	* @brief Color blend attachment state descriptor
	* 
	* Defines the blending configuration for a single framebuffer attachment,
	* including blend factors, operations, and color write mask. Controls how
	* incoming fragment colors are combined with existing framebuffer colors.
	*/
	struct ColorBlendAttachmentStateDesc
	{
		bool blendEnable = false;
		types::EBlendFactor srcColorBlendFactor = types::EBlendFactor::ONE;
		types::EBlendFactor dstColorBlendFactor = types::EBlendFactor::ZERO;
		types::EBlendOp colorBlendOp = types::EBlendOp::ADD;
		types::EBlendFactor srcAlphaBlendFactor = types::EBlendFactor::ONE;
		types::EBlendFactor dstAlphaBlendFactor = types::EBlendFactor::ZERO;
		types::EBlendOp alphaBlendOp = types::EBlendOp::ADD;
		types::EColorComponentFlags colorWriteMask = types::EColorComponentFlags::ALL;
	};

	/**
	 * @brief Color blend state descriptor for graphics pipelines
	 * 
	 * Defines the global color blending configuration for a graphics pipeline,
	 * including logical operations and per-attachment blend states. Controls
	 * how fragment colors are combined with framebuffer colors during rendering.
	 */
	struct ColorBlendStateDesc
	{
		bool logicOpEnable = false;
		types::ELogicOp logicOp = types::ELogicOp::COPY;
		std::span<const ColorBlendAttachmentStateDesc> attachments;
		std::array<float, 4> blendConstants = { 0.0f, 0.0f, 0.0f, 0.0f };
	};
}
