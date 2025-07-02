/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/types/EGraphicsBackend.h>
#include <orhi/types/EFormat.h>

namespace orhi::apii
{
	template<types::EGraphicsBackend Backend, class Context>
	class TRenderPass final
	{
	public:
		/**
		* Creates a render pass using the give format
		*/
		TRenderPass(types::EFormat p_format);

		/**
		* Destroys the render pass
		*/
		~TRenderPass();

	private:
		Context m_context;
	};
}
