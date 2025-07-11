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
	template<types::EGraphicsBackend Backend, CTX_SIG_DCL>
	class TDescriptorPool final
	{
	public:
		/**
		* Creates a descriptor pool
		*/
		TDescriptorPool(
			TDevice<Backend, CTX_SIG_FWD>& p_device,
			const data::DescriptorPoolDesc& p_desc
		);

		/**
		* Destroys the descriptor pool
		*/
		~TDescriptorPool();

		/**
		* Allocates descriptor sets
		*/
		std::vector<std::reference_wrapper<TDescriptorSet<Backend, CTX_SIG_FWD>>> AllocateDescriptorSets(
			const TDescriptorSetLayout<Backend, CTX_SIG_FWD>& p_layout,
			uint32_t p_count
		);

		/**
		* Returns the underlying object's native handle
		*/
		data::NativeHandle GetNativeHandle() const;

	private:
		DescriptorPoolContext m_context;
	};
}
