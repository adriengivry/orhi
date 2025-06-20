/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <bitset>
#include <cstdint>

#include <orhi/types/EBlendingEquation.h>
#include <orhi/types/EBlendingFactor.h>
#include <orhi/types/EComparaisonAlgorithm.h>
#include <orhi/types/ECullFace.h>
#include <orhi/types/ECullingOptions.h>
#include <orhi/types/EOperation.h>
#include <orhi/types/EPixelDataFormat.h>
#include <orhi/types/EPixelDataType.h>
#include <orhi/types/EPrimitiveMode.h>
#include <orhi/types/ERasterizationMode.h>
#include <orhi/types/ERenderingCapability.h>

namespace orhi::data
{
	/**
	* Represents the current state of the driver and allow for efficient context switches
	* @note because we target 64-bit architecture, the data bus can be expected to be 8 bytes wide
	* so copying 4 bytes will end-up copying 8 bytes. Therefore, we should try to align this struct
	* to take a multiple of 8 bytes.
	*/
	struct PipelineState
	{
		union
		{
			struct
			{
				// B0
				uint8_t stencilWriteMask : 8;

				// B1
				uint8_t stencilFuncRef : 8;

				// B2
				uint8_t stencilFuncMask : 8;

				// B3
				types::EComparaisonAlgorithm stencilFuncOp : 3;
				types::EOperation stencilOpFail : 3;
				types::ECullFace cullFace : 2;

				// B4
				types::EOperation depthOpFail : 3;
				types::EOperation bothOpFail : 3;
				types::ERasterizationMode rasterizationMode : 2;

				// B5
				uint8_t lineWidthPow2 : 3;
				types::EComparaisonAlgorithm depthFunc : 3;
				bool depthWriting : 1;
				bool blending : 1;

				// B6
				bool culling : 1;
				bool sampleAlphaToCoverage : 1;
				bool polygonOffsetFill : 1;
				bool multisample : 1;
				bool depthTest : 1;
				bool stencilTest : 1;
				bool scissorTest : 1;
				bool dither : 1;

				// B7
				union
				{
					struct
					{
						bool r : 1;
						bool g : 1;
						bool b : 1;
						bool a : 1;
					};

					uint8_t mask : 4;
				} colorWriting;
				// 4 bytes left in B7

				// B8
				types::EBlendingFactor blendingSrcFactor : 5;
				types::EBlendingEquation blendingEquation : 3;

				// B9
				types::EBlendingFactor blendingDestFactor : 5;
				// 3 bits left in B9
			};

			// Please don't access this directly, the layout is not guaranteed to stay the same!
			std::bitset<128> _bits;

			// Same as above, don't access this directly!
			uint8_t _bytes[16];
		};

		// Default pipeline state settings
		PipelineState() :
			colorWriting{ true, true, true, true },
			depthWriting(true),
			culling(true),
			dither(false),
			polygonOffsetFill(false),
			sampleAlphaToCoverage(false),
			depthTest(true),
			scissorTest(false),
			stencilTest(false),
			multisample(true),
			rasterizationMode(types::ERasterizationMode::FILL),
			stencilFuncOp(types::EComparaisonAlgorithm::ALWAYS),
			stencilFuncRef(0x00),
			stencilFuncMask(0xFF),
			stencilWriteMask(0xFF),
			stencilOpFail(types::EOperation::KEEP),
			depthOpFail(types::EOperation::KEEP),
			bothOpFail(types::EOperation::KEEP),
			depthFunc(types::EComparaisonAlgorithm::LESS),
			cullFace(types::ECullFace::BACK),
			lineWidthPow2(0x00),
			blending(false),
			blendingSrcFactor(types::EBlendingFactor::SRC_ALPHA),
			blendingEquation(types::EBlendingEquation::FUNC_ADD),
			blendingDestFactor(types::EBlendingFactor::ONE_MINUS_SRC_ALPHA)
		{}
	};
}
