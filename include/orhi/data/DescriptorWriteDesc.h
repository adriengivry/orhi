/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/types/EDescriptorType.h>
#include <orhi/types/EGraphicsBackend.h>
#include <orhi/api/TDescriptor.h>
#include <orhi/api/TBuffer.h>
#include <cstdint>
#include <variant>

namespace orhi::data
{
	template<types::EGraphicsBackend Backend, CTX_SIG_DCL>
	struct TextureSamplerDescriptorWriteInfo
	{
		using Descriptor = api::TDescriptor<Backend, CTX_SIG_FWD>;

		Descriptor& textureDescriptor;
		Descriptor& samplerDescriptor;
		types::EDescriptorType descriptorType = types::EDescriptorType::COMBINED_IMAGE_SAMPLER;
	};

	template<types::EGraphicsBackend Backend, CTX_SIG_DCL>
	struct BufferDescriptorWriteInfo
	{
		using Buffer = api::TBuffer<Backend, CTX_SIG_FWD>;

		Buffer& bufferDescriptor;
		types::EDescriptorType descriptorType = types::EDescriptorType::UNIFORM_BUFFER;
	};

	template<types::EGraphicsBackend Backend, CTX_SIG_DCL>
	using DescriptorWriteDesc = std::variant<
		TextureSamplerDescriptorWriteInfo<Backend, CTX_SIG_FWD>,
		BufferDescriptorWriteInfo<Backend, CTX_SIG_FWD>
	>;
}
