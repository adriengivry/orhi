/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/types/EGraphicsBackend.h>

namespace orhi::api
{
	template<types::EGraphicsBackend Backend, class Context>
	class TCommandPool final
	{
	public:


	private:
		Context m_context;
	};
}
