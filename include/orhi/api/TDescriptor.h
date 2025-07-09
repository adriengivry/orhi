/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <optional>
#include <orhi/api/TDevice.h>
#include <orhi/data/BufferMemoryRange.h>
#include <orhi/data/NativeHandle.h>
#include <orhi/data/TextureViewDesc.h>
#include <orhi/types/EGraphicsBackend.h>

namespace orhi::api
{
	template<types::EGraphicsBackend Backend, class Context, class DeviceContext, class TextureContext>
	class TDescriptor final
	{
	public:
		using TextureViewDesc = data::TextureViewDesc<
			Backend,
			TextureContext,
			DeviceContext
		>;

		/**
		* Creates a descriptor for a texture
		* @param p_device
		* @param p_desc
		*/
		TDescriptor(
			TDevice<Backend, DeviceContext>& p_device,
			const TextureViewDesc& p_desc
		);

		/**
		* Destroys the descriptor
		*/
		~TDescriptor();

		/**
		* Returns the underlying object's native handle
		*/
		data::NativeHandle GetNativeHandle() const;

	private:
		Context m_context;
	};
}
