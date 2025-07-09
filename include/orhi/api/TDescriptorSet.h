/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/types/EGraphicsBackend.h>
#include <orhi/types/EDescriptorType.h>
#include <orhi/api/TBuffer.h>
#include <orhi/data/NativeHandle.h>
#include <span>

namespace orhi::api
{
	template<types::EGraphicsBackend Backend, class Context, class DeviceContext, class BufferContext>
	class TDescriptorSet final
	{
	public:
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
			types::EDescriptorType p_type,
			std::span<const std::reference_wrapper<TBuffer<Backend, BufferContext, DeviceContext>>> p_buffers
		);

		/**
		* Returns the underlying object's native handle
		*/
		data::NativeHandle GetNativeHandle() const;

	private:
		Context m_context;
	};
}
