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
	template<types::EGraphicsBackend Backend, class Context, class DeviceContext, class BufferContext, class DescriptorContext, class TextureContext>
	class TDescriptorSet final
	{
	public:
		using DescriptorWriteDesc = data::DescriptorWriteDesc<
			Backend,
			DescriptorContext,
			DeviceContext,
			TextureContext,
			BufferContext
		>;

		/**
		* Creates a descriptor set
		*/
		TDescriptorSet(
			TDevice<Backend, DeviceContext>& p_device,
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
			const std::unordered_map<uint32_t, DescriptorWriteDesc>& p_writeDescs
		);

		/**
		* Returns the underlying object's native handle
		*/
		data::NativeHandle GetNativeHandle() const;

	private:
		Context m_context;
	};
}
