/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <optional>
#include <orhi/data/BufferMemoryRange.h>
#include <orhi/data/NativeHandle.h>
#include <orhi/data/SamplerDesc.h>
#include <orhi/data/TextureViewDesc.h>
#include <orhi/types/EGraphicsBackend.h>

namespace orhi::api
{
	template<typename BackendTraits> class TDevice;

	template<typename BackendTraits>
	class TDescriptor final
	{
	public:
		/**
		* Creates a descriptor for a texture
		* @param p_device
		* @param p_desc
		*/
		TDescriptor(
			TDevice<BackendTraits>& p_device,
			const data::TextureViewDesc<BackendTraits>& p_desc
		);

		/**
		* Creates a descriptor for a sampler
		* @param p_device
		* @param p_desc
		*/
		TDescriptor(
			TDevice<BackendTraits>& p_device,
			const data::SamplerDesc& p_desc
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
		BackendTraits::DescriptorContext m_context;
	};
}
