/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/data/DescriptorWriteDesc.h>
#include <orhi/data/NativeHandle.h>
#include <orhi/types/EDescriptorType.h>
#include <orhi/types/EGraphicsBackend.h>

#include <unordered_map>

namespace orhi::api
{
	template<typename BackendTraits> class TBuffer;
	template<typename BackendTraits> class TDevice;

	template<typename BackendTraits>
	class TDescriptorSet final
	{
	public:
		/**
		* Creates a descriptor set
		*/
		TDescriptorSet(
			TDevice<BackendTraits>& p_device,
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
			const std::unordered_map<uint32_t, data::DescriptorWriteDesc<BackendTraits>>& p_writeDescs
		);

		/**
		* Returns the underlying object's native handle
		*/
		data::NativeHandle GetNativeHandle() const;

	private:
		BackendTraits::DescriptorSetContext m_context;
	};
}
