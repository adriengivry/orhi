/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/types/ECompareOp.h>
#include <orhi/types/EFilter.h>
#include <orhi/types/EFormat.h>
#include <orhi/types/EGraphicsBackend.h>
#include <orhi/types/ESamplerAddressMode.h>
#include <orhi/types/ESamplerMipmapMode.h>
#include <orhi/types/ESampleCountFlags.h>
#include <orhi/types/ETextureLayout.h>
#include <orhi/types/ETextureTiling.h>
#include <orhi/types/ETextureType.h>
#include <orhi/types/ETextureUsageType.h>

#include <cstdint>

namespace orhi::data
{
	/**
	* @brief Descriptor for texture sampler creation
	* 
	* Defines the sampling configuration for textures, including filtering modes,
	* address modes for texture coordinate wrapping, anisotropic filtering,
	* and comparison operations for shadow mapping.
	*/
	struct SamplerDesc
	{
		types::EFilter magFilter = types::EFilter::LINEAR;
		types::EFilter minFilter = types::EFilter::LINEAR;
		types::ESamplerAddressMode addressModeU = types::ESamplerAddressMode::REPEAT;
		types::ESamplerAddressMode addressModeV = types::ESamplerAddressMode::REPEAT;
		types::ESamplerAddressMode addressModeW = types::ESamplerAddressMode::REPEAT;
		bool anisotropy = false;
		bool unnormalizedCoordinates = false;
		bool compareEnable = false;
		types::ECompareOp compareOp = types::ECompareOp::ALWAYS;
		types::ESamplerMipmapMode mipmapMode = types::ESamplerMipmapMode::LINEAR;
		float mipLodBias = 0.0f;
		float minLod = 0.0f;
		float maxLod = 0.0f;
	};
}
