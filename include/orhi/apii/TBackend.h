/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <vector>
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
		* Creates the backend.
		* @param p_extensions Extensions to use
		* @param p_debug Indicates whether to enable debug mode.
		*/
		TBackend(
			const std::vector<std::string>& p_extenions,
			bool p_debug
		);

		/**
		* Destroys the backend.
		*/
		~TBackend();

	private:
		Context m_context;
	};
}
