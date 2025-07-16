/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/impl/common/NativeHandle.h>

namespace orhi::impl::common
{
	/**
	* @brief Base class for all backend-specific objects.
	* 
	* This class serves as a base for all objects that need to store a native handle.
	* It provides a common interface for accessing the native handle and prevents
	* copying or moving of the object to ensure the handle remains valid.
	*/
	class BackendObject
	{
	public:
		/**
		* @brief Gets the native handle of the backend object
		* @return A handle to the underlying native object
		*/
		inline const NativeHandle GetNativeHandle() const { return m_handle; }

		/**
		* @brief Implicit conversion to the native handle type
		* @return The native handle of the backend object
		*/
		inline operator NativeHandle() const { return GetNativeHandle(); }

	protected:
		BackendObject() = default;
		BackendObject(NativeHandle p_handle) { m_handle = p_handle; }
		~BackendObject() = default;
		BackendObject(const BackendObject&& p_object) = delete;
		BackendObject& operator=(BackendObject&&) = delete;
		BackendObject(const BackendObject&) = delete;
		BackendObject& operator=(const BackendObject&) = delete;

	protected:
		NativeHandle m_handle;
	};
}
