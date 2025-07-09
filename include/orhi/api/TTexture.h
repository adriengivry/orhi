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
#include <orhi/data/TextureDesc.h>
#include <orhi/types/EGraphicsBackend.h>
#include <orhi/types/EMemoryPropertyFlags.h>

namespace orhi::api
{
	template<types::EGraphicsBackend Backend, class Context, class DeviceContext>
	class TTexture final
	{
	public:
		/**
		* Creates a texture
		* @param p_device
		* @param p_desc
		*/
		TTexture(
			TDevice<Backend, DeviceContext>& p_device,
			const data::TextureDesc& p_desc
		);

		/**
		* Destroys the texture
		*/
		~TTexture();

		/**
		* Returns true if the texture is allocated
		*/
		bool IsAllocated() const;

		/**
		* Allocate memory for the texture
		*/
		void Allocate(types::EMemoryPropertyFlags p_properties);

		/**
		* Deallocates memory for the texture
		*/
		void Deallocate();

		/**
		* Uploads data to the allocated memory
		*/
		void Upload(const void* p_data, std::optional<data::BufferMemoryRange> p_memoryRange = std::nullopt);

		/**
		* Returns allocated bytes
		*/
		uint64_t GetAllocatedBytes() const;

		/**
		* Returns the underlying object's native handle
		*/
		data::NativeHandle GetNativeHandle() const;

	private:
		Context m_context;
	};
}
