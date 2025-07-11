/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/data/BufferMemoryRange.h>
#include <orhi/data/NativeHandle.h>
#include <orhi/data/TextureDesc.h>
#include <orhi/types/EFormat.h>
#include <orhi/types/EGraphicsBackend.h>
#include <orhi/types/EMemoryPropertyFlags.h>
#include <orhi/types/ETextureLayout.h>

#include <optional>

namespace orhi::api
{
	template<typename BackendTraits> class TDevice;

	template<typename BackendTraits>
	class TTexture final
	{
	public:
		/**
		* Creates a texture
		* @param p_device
		* @param p_desc
		*/
		TTexture(
			TDevice<BackendTraits>& p_device,
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
		* Notifies the texture that its layout changed. This should be called by the backend after each
		* layout transition, and in most cases, shouldn't be used manually.
		*/
		void NotifyLayoutChange(types::ETextureLayout p_layout);

		/**
		* Returns allocated bytes
		*/
		uint64_t GetAllocatedBytes() const;

		/**
		* Returns the texture format 
		*/
		types::EFormat GetFormat() const;

		/**
		* Returns the texture layout
		*/
		types::ETextureLayout GetLayout() const;

		/**
		* Returns the texture extent 
		*/
		const data::Extent3D& GetExtent() const;

		/**
		* Returns the underlying object's native handle
		*/
		data::NativeHandle GetNativeHandle() const;

	private:
		BackendTraits::TextureContext m_context;
	};
}
