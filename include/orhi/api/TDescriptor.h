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
#include <orhi/data/SamplerDesc.h>
#include <orhi/types/EGraphicsBackend.h>

namespace orhi::api
{
	template<types::EGraphicsBackend Backend, typename ContextRegistry>
	class TDescriptor final
	{
	public:
		/**
		* Creates a descriptor for a texture
		* @param p_device
		* @param p_desc
		*/
		TDescriptor(
			TDevice<Backend, ContextRegistry>& p_device,
			const data::TextureViewDesc<Backend, ContextRegistry>& p_desc
		);

		/**
		* Creates a descriptor for a sampler
		* @param p_device
		* @param p_desc
		*/
		TDescriptor(
			TDevice<Backend, ContextRegistry>& p_device,
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
		typename ContextRegistry::DescriptorContext m_context;
	};
}
