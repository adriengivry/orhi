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
	template<types::EGraphicsBackend Backend, typename ContextRegistry>
	struct TextureSamplerDescriptorWriteInfo
	{
		using Descriptor = api::TDescriptor<Backend, ContextRegistry>;

		Descriptor& textureDescriptor;
		Descriptor& samplerDescriptor;
		types::EDescriptorType descriptorType = types::EDescriptorType::COMBINED_IMAGE_SAMPLER;
	};

	template<types::EGraphicsBackend Backend, typename ContextRegistry>
	struct BufferDescriptorWriteInfo
	{
		using Buffer = api::TBuffer<Backend, ContextRegistry>;

		Buffer& bufferDescriptor;
		types::EDescriptorType descriptorType = types::EDescriptorType::UNIFORM_BUFFER;
	};

	template<types::EGraphicsBackend Backend, typename ContextRegistry>
	using DescriptorWriteDesc = std::variant<
		TextureSamplerDescriptorWriteInfo<Backend, ContextRegistry>,
		BufferDescriptorWriteInfo<Backend, ContextRegistry>
	>;
}
