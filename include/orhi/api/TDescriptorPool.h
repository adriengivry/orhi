/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/data/DescriptorPoolDesc.h>
#include <orhi/data/NativeHandle.h>
#include <orhi/types/EGraphicsBackend.h>

#include <vector>

namespace orhi::api
{
	template<typename BackendTraits> class TDescriptorSet;
	template<typename BackendTraits> class TDescriptorSetLayout;
	template<typename BackendTraits> class TDevice;

	template<typename BackendTraits>
	class TDescriptorPool final
	{
	public:
		/**
		* Creates a descriptor pool
		*/
		TDescriptorPool(
			TDevice<BackendTraits>& p_device,
			const data::DescriptorPoolDesc& p_desc
		);

		/**
		* Destroys the descriptor pool
		*/
		~TDescriptorPool();

		/**
		* Allocates descriptor sets
		*/
		std::vector<std::reference_wrapper<TDescriptorSet<BackendTraits>>> AllocateDescriptorSets(
			const TDescriptorSetLayout<BackendTraits>& p_layout,
			uint32_t p_count
		);

		/**
		* Returns the underlying object's native handle
		*/
		data::NativeHandle GetNativeHandle() const;

	private:
		BackendTraits::DescriptorPoolContext m_context;
	};
}
