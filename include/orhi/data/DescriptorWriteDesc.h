/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/types/EDescriptorType.h>
#include <orhi/types/EGraphicsBackend.h>

#include <cstdint>
#include <variant>

namespace orhi::api
{
	template<typename BackendTraits> class TBuffer;
	template<typename BackendTraits> class TDescriptor;
}

namespace orhi::data
{
	template<typename BackendTraits>
	struct TextureSamplerDescriptorWriteInfo
	{
		using Descriptor = api::TDescriptor<BackendTraits>;

		Descriptor& textureDescriptor;
		Descriptor& samplerDescriptor;
		types::EDescriptorType descriptorType = types::EDescriptorType::COMBINED_IMAGE_SAMPLER;
	};

	template<typename BackendTraits>
	struct BufferDescriptorWriteInfo
	{
		using Buffer = api::TBuffer<BackendTraits>;

		Buffer& bufferDescriptor;
		types::EDescriptorType descriptorType = types::EDescriptorType::UNIFORM_BUFFER;
	};

	template<typename BackendTraits>
	using DescriptorWriteDesc = std::variant<
		TextureSamplerDescriptorWriteInfo<BackendTraits>,
		BufferDescriptorWriteInfo<BackendTraits>
	>;
}
