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
	template<types::EGraphicsBackend Backend, class DescriptorContext, class DeviceContext, class TextureContext>
	struct TextureSamplerDescriptorWriteInfo
	{
		using Descriptor = api::TDescriptor<Backend, DescriptorContext, DeviceContext, TextureContext>;

		Descriptor& textureDescriptor;
		Descriptor& samplerDescriptor;
		types::EDescriptorType descriptorType = types::EDescriptorType::COMBINED_IMAGE_SAMPLER;
	};

	template<types::EGraphicsBackend Backend, class BufferContext, class DeviceContext>
	struct BufferDescriptorWriteInfo
	{
		using Buffer = api::TBuffer<Backend, BufferContext, DeviceContext>;

		Buffer& bufferDescriptor;
		types::EDescriptorType descriptorType = types::EDescriptorType::UNIFORM_BUFFER;
	};

	template<types::EGraphicsBackend Backend, class DescriptorContext, class DeviceContext, class TextureContext, class BufferContext>
	using DescriptorWriteDesc = std::variant<
		TextureSamplerDescriptorWriteInfo<Backend, DescriptorContext, DeviceContext, TextureContext>,
		BufferDescriptorWriteInfo<Backend, BufferContext, DeviceContext>
	>;
}
