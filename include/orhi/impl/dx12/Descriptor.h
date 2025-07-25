/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry, Jian Bang Xu
* @licence: MIT
*/

#pragma once

#include <orhi/api/TDescriptor.h>
#include <orhi/impl/dx12/BackendTraits.h>
#include <orhi/impl/dx12/Device.h>
#include <orhi/types/EDescriptorType.h>
#include <orhi/types/EFormat.h>
#include <orhi/types/ETextureLayout.h>

namespace orhi::impl::dx12
{
	enum class EDirectXDescriptorType
	{
		NONE = 0,
		CBV_SRV_UAV,
		SAMPLER,

		BUFFER_VIEW = CBV_SRV_UAV,
		IMAGE_VIEW = CBV_SRV_UAV,
	};

	struct DescriptorContext
	{
		Device& device;
		EDirectXDescriptorType type;
		uint64_t handle;
	};

	using Descriptor = api::TDescriptor<BackendTraits>;
}
