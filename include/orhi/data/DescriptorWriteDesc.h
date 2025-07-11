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
	template<typename ContextRegistry>
	struct TextureSamplerDescriptorWriteInfo
	{
		using Descriptor = api::TDescriptor<ContextRegistry>;

		Descriptor& textureDescriptor;
		Descriptor& samplerDescriptor;
		types::EDescriptorType descriptorType = types::EDescriptorType::COMBINED_IMAGE_SAMPLER;
	};

	template<typename ContextRegistry>
	struct BufferDescriptorWriteInfo
	{
		using Buffer = api::TBuffer<ContextRegistry>;

		Buffer& bufferDescriptor;
		types::EDescriptorType descriptorType = types::EDescriptorType::UNIFORM_BUFFER;
	};

	template<typename ContextRegistry>
	using DescriptorWriteDesc = std::variant<
		TextureSamplerDescriptorWriteInfo<ContextRegistry>,
		BufferDescriptorWriteInfo<ContextRegistry>
	>;
}
