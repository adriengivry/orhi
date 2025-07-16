/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/data/DescriptorPoolDesc.h>
#include <orhi/detail/Object.h>
#include <orhi/types/EGraphicsBackend.h>

#include <vector>

namespace orhi::api
{
	template<typename BackendTraits> class TDescriptorSet;
	template<typename BackendTraits> class TDescriptorSetLayout;
	template<typename BackendTraits> class TDevice;

	/**
	* @brief A pool for allocating descriptor sets
	* 
	* TDescriptorPool manages the allocation of descriptor sets and provides memory
	* for the descriptors contained within those sets. The pool is created with
	* a maximum number of sets and descriptors that can be allocated.
	* 
	* @tparam BackendTraits Backend-specific traits defining implementation types
	*/
	template<typename BackendTraits>
	class TDescriptorPool final : public detail::Object
	{
	public:
		/**
		* @brief Creates a descriptor pool with the specified properties
		* @param p_device Reference to the device that will own this descriptor pool
		* @param p_desc Descriptor pool descriptor specifying maximum sets and descriptor counts
		*/
		TDescriptorPool(
			TDevice<BackendTraits>& p_device,
			const data::DescriptorPoolDesc& p_desc
		);

		/**
		* @brief Destroys the descriptor pool and all associated descriptor sets
		*/
		~TDescriptorPool();

		/**
		* @brief Allocates descriptor sets from this pool
		* @param p_layout The descriptor set layout defining the structure of the sets
		* @param p_count Number of descriptor sets to allocate
		* @return Vector of references to the allocated descriptor sets
		*/
		std::vector<std::reference_wrapper<TDescriptorSet<BackendTraits>>> AllocateDescriptorSets(
			const TDescriptorSetLayout<BackendTraits>& p_layout,
			uint32_t p_count
		);

	private:
		BackendTraits::DescriptorPoolContext m_context;
	};
}
