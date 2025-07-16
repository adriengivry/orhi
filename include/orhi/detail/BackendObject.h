/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/data/NativeHandle.h>

namespace orhi::detail
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
		BackendObject(data::NativeHandle p_handle) { m_handle = p_handle; }
		BackendObject() = default;
		~BackendObject() = default;

		// Non-movable
		BackendObject(const BackendObject&& p_object) = delete;
		BackendObject& operator=(BackendObject&&) = delete;

		// Non-copyable
		BackendObject(const BackendObject&) = delete;
		BackendObject& operator=(const BackendObject&) = delete;

		const data::NativeHandle GetNativeHandle() const { return m_handle; }
		inline operator data::NativeHandle () { return GetNativeHandle(); }

	protected:
		data::NativeHandle m_handle;
	};
}
