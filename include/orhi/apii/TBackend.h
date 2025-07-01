/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/types/EGraphicsBackend.h>

namespace orhi::apii
{
	/**
	* Backend class that wraps the selected graphics API's context.
	*/
	template<types::EGraphicsBackend Backend, class Context>
	class TBackend final
	{
	public:
		/**
		* Initializes the backend.
		* @param debug Indicates whether to enable debug mode.
		*/
		void Init(bool p_debug);

	private:
		Context m_context;
	};
}
