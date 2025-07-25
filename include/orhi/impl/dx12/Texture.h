/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry, Jian Bang Xu
* @licence: MIT
*/

#pragma once

#include <orhi/api/TTexture.h>
#include <orhi/impl/dx12/BackendTraits.h>
#include <orhi/impl/dx12/detail/ComPtr.h>
#include <orhi/impl/dx12/Device.h>
#include <orhi/types/EFormat.h>
#include <orhi/types/ETextureLayout.h>

struct ID3D12Resource;

namespace orhi::impl::dx12
{
	struct TextureContext
	{
		Device& device;
		Microsoft::WRL::ComPtr<ID3D12Resource> memory;
		types::EFormat format;
		uint32_t mipLevels;
		math::Extent3D extent;
		uint64_t allocatedBytes;
	};

	using Texture = api::TTexture<BackendTraits>;
}
