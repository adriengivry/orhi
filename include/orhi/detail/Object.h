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
	* @brief 
	*/
	class Object
	{
	public:
		Object(data::NativeHandle p_handle) { m_handle = p_handle; }
		Object() = default;
		~Object() = default;
		// Object(const Object&) = delete;
		// Object(const Object&&) = delete;
		// Object& operator=(const Object&) = delete;
		// Object& operator=(Object&&) = delete;
		const data::NativeHandle GetNativeHandle() const { return m_handle; }
		inline operator data::NativeHandle () { return GetNativeHandle(); }

	protected:
		data::NativeHandle m_handle;
	};
}
