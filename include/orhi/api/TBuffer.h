/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/api/TBackendTraits.h>
#include <orhi/data/BufferDesc.h>
#include <orhi/data/MemoryRange.h>
#include <orhi/detail/BackendObject.h>
#include <orhi/types/EGraphicsBackend.h>
#include <orhi/types/EMemoryPropertyFlags.h>

#include <optional>

namespace orhi::api
{
	template<typename BackendTraits> class TDevice;

	/**
	* @brief A buffer object that represents a contiguous block of memory for storing data
	* 
	* TBuffer provides a cross-platform abstraction for buffer objects, which can be used
	* for storing vertex data, index data, uniform data, or any other type of accessible data.
	* The buffer must be allocated before use and can be uploaded with data from the CPU.
	* 
	* @tparam BackendTraits Backend-specific traits defining implementation types
	*/
	template<typename BackendTraits>
	class TBuffer final : public detail::BackendObject
	{
	public:
		/**
		* @brief Creates a buffer with the specified properties
		* @param p_device Reference to the device that will own this buffer
		* @param p_desc Buffer creation descriptor specifying size, usage flags, and other properties
		*/
		TBuffer(
			TDevice<BackendTraits>& p_device,
			const data::BufferDesc& p_desc
		);

		/**
		* @brief Destroys the buffer and releases associated resources
		*/
		~TBuffer();

		/**
		* @brief Checks if the buffer has allocated memory
		* @return True if the buffer has allocated memory, false otherwise
		*/
		bool IsAllocated() const;

		/**
		* @brief Allocates memory for the buffer with specified properties
		* @param p_properties Memory property flags specifying the type of memory to allocate (e.g., device-local, host-visible)
		*/
		void Allocate(types::EMemoryPropertyFlags p_properties);

		/**
		* @brief Deallocates the buffer's memory
		* @note The buffer object remains valid but cannot be used until reallocated
		*/
		void Deallocate();

		/**
		* @brief Uploads data to the allocated buffer memory
		* @param p_data Pointer to the source data to upload
		* @param p_memoryRange Optional memory range specifying offset and size; if not provided, the entire buffer is used
		*/
		void Upload(const void* p_data, std::optional<data::MemoryRange> p_memoryRange = std::nullopt);

		/**
		* @brief Gets the number of bytes currently allocated for this buffer
		* @return The number of allocated bytes
		*/
		uint64_t GetAllocatedBytes() const;

	private:
		BackendTraits::BufferContext m_context;
	};
}
