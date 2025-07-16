/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/types/EFormat.h>

#include <cstdint>

namespace orhi::data
{
	/**
	* @brief Wrapper class for native graphics API handles
	* 
	* Provides a type-safe wrapper around void pointers that represent
	* backend-specific graphics objects. Allows safe casting to the
	* appropriate native types when interfacing with backend APIs.
	*/
	class NativeHandle
	{
	public:
		/**
		* @brief Default constructor creating an empty handle
		*/
		NativeHandle() : m_handle(nullptr) {}

		/**
		* @brief Constructor from a raw pointer
		* @param p_ptr Raw pointer to the native handle
		*/
		NativeHandle(void* p_ptr) : m_handle(p_ptr) {}

		/**
		* @brief Converts the handle to a specific type
		* @tparam T The type to cast the handle to
		* @return The handle cast to the specified type
		*/
		template<class T>
		inline T As() const { return static_cast<T>(m_handle); }

		/**
		* @brief Converts the handle to a specific type
		* @tparam T The type to cast the handle to
		* @return The handle cast to the specified type
		*/
		template<class T>
		inline T ReinterpretAs() { return reinterpret_cast<T>(m_handle); }

	private:
		void* m_handle = nullptr;
	};
}
