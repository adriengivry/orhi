/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <optional>
#include <orhi/api/TDevice.h>
#include <orhi/data/BufferDesc.h>
#include <orhi/data/NativeHandle.h>
#include <orhi/data/BufferMemoryRange.h>
#include <orhi/types/EGraphicsBackend.h>
#include <orhi/types/EMemoryPropertyFlags.h>
#include <orhi/api/TContextRegistry.h>

namespace orhi::api
{
	template<types::EGraphicsBackend Backend, typename ContextRegistry>
	class TBuffer final
	{
	public:
		/**
		* Creates a buffer
		* @param p_device
		* @param p_desc
		*/
		TBuffer(
			TDevice<Backend, ContextRegistry>& p_device,
			const data::BufferDesc& p_desc
		);

		/**
		* Destroys the buffer
		*/
		~TBuffer();

		/**
		* Returns true if the buffer is allocated
		*/
		bool IsAllocated() const;

		/**
		* Allocate memory for the buffer
		*/
		void Allocate(types::EMemoryPropertyFlags p_properties);

		/**
		* Deallocates memory for the buffer
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
		typename ContextRegistry::BufferContext m_context;
	};
}
