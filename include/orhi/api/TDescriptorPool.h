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
	template<
		types::EGraphicsBackend Backend,
		class DescriptorPoolContext,
		class DeviceContext,
		class DescriptorSetContext,
		class DescriptorSetLayoutContext,
		class BufferContext,
		class DescriptorContext,
		class TextureContext
	>
	class TDescriptorPool final
	{
	public:
		/**
		* Creates a descriptor pool
		*/
		TDescriptorPool(
			TDevice<Backend, DeviceContext>& p_device,
			const data::DescriptorPoolDesc& p_desc
		);

		/**
		* Destroys the descriptor pool
		*/
		~TDescriptorPool();

		/**
		* Allocates descriptor sets
		*/
		std::vector<std::reference_wrapper<TDescriptorSet<Backend, DescriptorSetContext, DeviceContext, BufferContext, DescriptorContext, TextureContext>>> AllocateDescriptorSets(
			const TDescriptorSetLayout<Backend, DescriptorSetLayoutContext, DeviceContext>& p_layout,
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
