/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/data/MemoryRange.h>
#include <orhi/data/SamplerDesc.h>
#include <orhi/data/TextureViewDesc.h>
#include <orhi/detail/BackendObject.h>
#include <orhi/types/EGraphicsBackend.h>

#include <optional>

namespace orhi::api
{
	template<typename BackendTraits> class TDevice;

	/**
	* @brief A descriptor representing a shader resource (texture view or sampler)
	* 
	* TDescriptor encapsulates individual shader resources that can be bound to descriptor sets.
	* Descriptors can represent texture views, samplers, or other shader-accessible resources.
	* 
	* @tparam BackendTraits Backend-specific traits defining implementation types
	*/
	template<typename BackendTraits>
	class TDescriptor final : public detail::BackendObject
	{
	public:
		/**
		* @brief Creates a descriptor for a texture view
		* @param p_device Reference to the device that will own this descriptor
		* @param p_desc Texture view descriptor specifying the texture and view parameters
		*/
		TDescriptor(
			TDevice<BackendTraits>& p_device,
			const data::TextureViewDesc& p_desc
		);

		/**
		* @brief Creates a descriptor for a sampler
		* @param p_device Reference to the device that will own this descriptor
		* @param p_desc Sampler descriptor specifying filtering and addressing modes
		*/
		TDescriptor(
			TDevice<BackendTraits>& p_device,
			const data::SamplerDesc& p_desc
		);

		/**
		* @brief Destroys the descriptor and releases associated resources
		*/
		~TDescriptor();

	private:
		BackendTraits::DescriptorContext m_context;
	};
}
