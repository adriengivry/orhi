/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/data/DescriptorWriteDesc.h>
#include <orhi/detail/BackendObject.h>
#include <orhi/types/EDescriptorType.h>
#include <orhi/types/EGraphicsBackend.h>

#include <unordered_map>

namespace orhi::api
{
	template<typename BackendTraits> class TBuffer;
	template<typename BackendTraits> class TDevice;

	/**
	* @brief A descriptor set containing shader resources
	* 
	* TDescriptorSet represents a collection of descriptors (buffers, textures, samplers)
	* that can be bound to a shader pipeline. Descriptor sets are allocated from descriptor
	* pools and must conform to a descriptor set layout.
	* 
	* @tparam BackendTraits Backend-specific traits defining implementation types
	*/
	template<typename BackendTraits>
	class TDescriptorSet final : public detail::BackendObject
	{
	public:
		/**
		* @brief Creates a descriptor set from a native handle
		* @param p_device Reference to the device that owns this descriptor set
		* @param p_handle Native handle to the underlying descriptor set object
		*/
		TDescriptorSet(
			TDevice<BackendTraits>& p_device,
			data::NativeHandle p_handle
		);

		/**
		* @brief Destroys the descriptor set and releases associated resources
		*/
		~TDescriptorSet();

		/**
		* @brief Updates the descriptor set with new resource bindings
		* @param p_writeDescs Map of binding indices to descriptor write descriptors specifying the resources to bind
		*/
		void Write(
			const std::unordered_map<uint32_t, data::DescriptorWriteDesc<BackendTraits>>& p_writeDescs
		);

	private:
		BackendTraits::DescriptorSetContext m_context;
	};
}
