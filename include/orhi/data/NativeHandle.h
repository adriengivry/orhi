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
	class NativeHandle
	{
	public:
		NativeHandle() : m_handle(nullptr)
		{

		}

		NativeHandle(void* p_ptr) :
			m_handle(p_ptr)
		{

		}

		template<class T>
		T As()
		{
			return static_cast<T>(m_handle);
		}

	private:
		void* m_handle = nullptr;
	};
}
