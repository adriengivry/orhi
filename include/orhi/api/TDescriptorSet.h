/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/types/EGraphicsBackend.h>
#include <orhi/types/EDescriptorType.h>
#include <orhi/api/TBuffer.h>
#include <orhi/api/TDevice.h>
#include <orhi/data/NativeHandle.h>
#include <orhi/data/DescriptorWriteDesc.h>
#include <unordered_map>

namespace orhi::api
{
	template<types::EGraphicsBackend Backend, typename ContextRegistry>
	class TDescriptorSet final
	{
	public:
		/**
		* Creates a descriptor set
		*/
		TDescriptorSet(
			TDevice<Backend, ContextRegistry>& p_device,
			data::NativeHandle p_handle
		);

		/**
		* Destroys the descriptor set
		*/
		~TDescriptorSet();

		/**
		* Attaches a list of buffers and images to the descriptor set.
		*/
		void Write(
			const std::unordered_map<uint32_t, data::DescriptorWriteDesc<Backend, ContextRegistry>>& p_writeDescs
		);

		/**
		* Returns the underlying object's native handle
		*/
		data::NativeHandle GetNativeHandle() const;

	private:
		typename ContextRegistry::DescriptorSetContext m_context;
	};
}
