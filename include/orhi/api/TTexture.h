/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/data/MemoryRange.h>
#include <orhi/data/NativeHandle.h>
#include <orhi/data/TextureDesc.h>
#include <orhi/math/Extent3D.h>
#include <orhi/types/EFormat.h>
#include <orhi/types/EGraphicsBackend.h>
#include <orhi/types/EMemoryPropertyFlags.h>
#include <orhi/types/ETextureLayout.h>

#include <optional>

namespace orhi::api
{
	template<typename BackendTraits> class TDevice;

	/**
	* @brief A texture object for storing image data on the GPU
	* 
	* TTexture represents a multi-dimensional array of image data that can be
	* used for rendering, as render targets, or for compute operations. Textures
	* must be allocated before use and can be uploaded with image data from the CPU.
	* 
	* @tparam BackendTraits Backend-specific traits defining implementation types
	*/
	template<typename BackendTraits>
	class TTexture final
	{
	public:
		/**
		* @brief Creates a texture with the specified properties
		* @param p_device Reference to the device that will own this texture
		* @param p_desc Texture descriptor specifying dimensions, format, usage, and other properties
		*/
		TTexture(
			TDevice<BackendTraits>& p_device,
			const data::TextureDesc& p_desc
		);

		/**
		* @brief Destroys the texture and releases associated resources
		*/
		~TTexture();

		/**
		* @brief Checks if the texture has allocated memory
		* @return True if the texture has allocated memory, false otherwise
		*/
		bool IsAllocated() const;

		/**
		* @brief Allocates memory for the texture with specified properties
		* @param p_properties Memory property flags specifying the type of memory to allocate
		*/
		void Allocate(types::EMemoryPropertyFlags p_properties);

		/**
		* @brief Deallocates the texture's memory
		* @note The texture object remains valid but cannot be used until reallocated
		*/
		void Deallocate();

		/**
		* @brief Uploads image data to the allocated texture memory
		* @param p_data Pointer to the source image data to upload
		* @param p_memoryRange Optional memory range specifying offset and size; if not provided, the entire texture is used
		*/
		void Upload(const void* p_data, std::optional<data::MemoryRange> p_memoryRange = std::nullopt);

		/**
		* @brief Gets the number of bytes currently allocated for this texture
		* @return The number of allocated bytes
		*/
		uint64_t GetAllocatedBytes() const;

		/**
		* @brief Gets the pixel format of the texture
		* @return The texture's pixel format
		*/
		types::EFormat GetFormat() const;

		/**
		* @brief Gets the dimensions of the texture
		* @return The texture's extent (width, height, depth)
		*/
		const math::Extent3D& GetExtent() const;

		/**
		* @brief Gets the mip level count of the texture
		* @return The number of mip levels in the texture
		*/
		uint32_t GetMipLevels() const;

		/**
		* @brief Gets the native handle for backend-specific operations
		* @return Native handle to the underlying texture object
		*/
		data::NativeHandle GetNativeHandle() const;

	private:
		BackendTraits::TextureContext m_context;
	};
}
