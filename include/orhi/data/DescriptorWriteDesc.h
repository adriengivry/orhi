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
	/**
	* @brief Texture and sampler descriptor write information
	* 
	* Contains the descriptors and type information needed to write
	* combined texture-sampler descriptors to a descriptor set binding.
	* 
	* @tparam BackendTraits Backend-specific traits defining implementation types
	*/
	template<typename BackendTraits>
	struct TextureSamplerDescriptorWriteInfo
	{
		using Descriptor = api::TDescriptor<BackendTraits>;

		Descriptor& textureDescriptor;
		Descriptor& samplerDescriptor;
		types::EDescriptorType descriptorType = types::EDescriptorType::COMBINED_IMAGE_SAMPLER;
	};

	/**
	* @brief Buffer descriptor write information
	* 
	* Contains the buffer descriptor and type information needed to write
	* buffer descriptors (uniform buffers, storage buffers, etc.) to a
	* descriptor set binding.
	* 
	* @tparam BackendTraits Backend-specific traits defining implementation types
	*/
	template<typename BackendTraits>
	struct BufferDescriptorWriteInfo
	{
		using Buffer = api::TBuffer<BackendTraits>;

		Buffer& bufferDescriptor;
		types::EDescriptorType descriptorType = types::EDescriptorType::UNIFORM_BUFFER;
	};

	/**
	* @brief Variant type for descriptor write operations
	* 
	* A variant that can hold either texture-sampler or buffer descriptor
	* write information, allowing unified handling of different descriptor
	* types when updating descriptor sets.
	* 
	* @tparam BackendTraits Backend-specific traits defining implementation types
	*/
	template<typename BackendTraits>
	using DescriptorWriteDesc = std::variant<
		TextureSamplerDescriptorWriteInfo<BackendTraits>,
		BufferDescriptorWriteInfo<BackendTraits>
	>;
}
