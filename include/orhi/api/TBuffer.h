/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <optional>

#include <orhi/types/EGraphicsBackend.h>
#include <orhi/types/EAccessSpecifier.h>
#include <orhi/types/EBufferType.h>
#include <orhi/data/BufferMemoryRange.h>

namespace orhi::api
{
	/**
	* Represents a buffer, used to store data on the GPU
	*/
	template<types::EGraphicsBackend Backend, class BufferContext>
	class TBuffer
	{
	public:
		/**
		* Creates a buffer
		* @param p_type
		*/
		TBuffer(types::EBufferType p_type);

		/**
		* Destroys the buffer
		*/
		~TBuffer();

		/**
		* Allocates memory for the buffer
		* @param p_size
		* @param p_usage
		* @return The size of the allocated memory in bytes
		*/
		uint64_t Allocate(uint64_t p_size, types::EAccessSpecifier p_usage = types::EAccessSpecifier::STATIC_DRAW);

		/**
		* Uploads data to the buffer
		* @param p_data
		* @param p_range
		*/
		void Upload(const void* p_data, std::optional<data::BufferMemoryRange> p_range = std::nullopt);

		/**
		* Returns true if the buffer is valid (properly allocated)
		*/
		bool IsValid() const;

		/**
		* Returns true if the buffer is empty
		*/
		bool IsEmpty() const;

		/**
		* Returns the size of the allocated buffer in bytes
		*/
		uint64_t GetSize() const;

		/**
		* Binds the buffer
		* @param p_index (Optional) Index to bind the buffer to
		*/
		void Bind(std::optional<uint32_t> p_index = std::nullopt) const;

		/**
		* Unbinds the buffer
		*/
		void Unbind() const;

		/**
		* Returns the ID of the buffer
		*/
		uint32_t GetID() const;

	protected:
		BufferContext m_buffer;
	};
}
