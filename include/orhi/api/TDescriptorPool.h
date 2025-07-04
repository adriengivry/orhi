/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/types/EGraphicsBackend.h>
#include <orhi/api/TDescriptorSetLayout.h>
#include <orhi/api/TDescriptorSet.h>
#include <vector>

namespace orhi::api
{
	template<types::EGraphicsBackend Backend, class Context, class DeviceContext, class DescriptorSetContext, class DescriptorSetLayoutContext, class BufferContext>
	class TDescriptorPool final
	{
	public:
		/**
		* Creates a descriptor pool
		*/
		TDescriptorPool(
			TDevice<Backend, DeviceContext>& p_device,
			uint32_t p_maxSetCount
		);

		/**
		* Destroys the descriptor pool
		*/
		~TDescriptorPool();

		/**
		* Allocates descriptor sets
		*/
		std::vector<std::reference_wrapper<TDescriptorSet<Backend, DescriptorSetContext, DeviceContext, BufferContext>>> AllocateDescriptorSets(
			const TDescriptorSetLayout<Backend, DescriptorSetLayoutContext, DeviceContext>& p_layout,
			uint32_t p_count
		);

		/**
		* Returns the underlying object's native handle
		*/
		data::NativeHandle GetNativeHandle() const;

	private:
		Context m_context;
	};
}
