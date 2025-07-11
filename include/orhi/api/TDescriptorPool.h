/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/types/EGraphicsBackend.h>
#include <orhi/api/TDescriptorSetLayout.h>
#include <orhi/api/TDescriptorSet.h>
#include <orhi/data/DescriptorPoolDesc.h>
#include <vector>

namespace orhi::api
{
	template<types::EGraphicsBackend Backend, typename ContextRegistry>
	class TDescriptorPool final
	{
	public:
		/**
		* Creates a descriptor pool
		*/
		TDescriptorPool(
			TDevice<Backend, ContextRegistry>& p_device,
			const data::DescriptorPoolDesc& p_desc
		);

		/**
		* Destroys the descriptor pool
		*/
		~TDescriptorPool();

		/**
		* Allocates descriptor sets
		*/
		std::vector<std::reference_wrapper<TDescriptorSet<Backend, ContextRegistry>>> AllocateDescriptorSets(
			const TDescriptorSetLayout<Backend, ContextRegistry>& p_layout,
			uint32_t p_count
		);

		/**
		* Returns the underlying object's native handle
		*/
		data::NativeHandle GetNativeHandle() const;

	private:
		ContextRegistry::DescriptorPoolContext m_context;
	};
}
