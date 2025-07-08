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
#include <span>
#include <array>

namespace orhi::data
{
	/**
	* Color blend attachment state descriptor
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
	* Color blend state descriptor
	*/
	struct ColorBlendStateDesc
	{
		bool logicOpEnable = false;
		types::ELogicOp logicOp = types::ELogicOp::COPY;
		std::span<const ColorBlendAttachmentStateDesc> attachments;
		std::array<float, 4> blendConstants = { 0.0f, 0.0f, 0.0f, 0.0f };
	};
}
