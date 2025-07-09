/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/types/EPrimitiveTopology.h>

namespace orhi::data
{
	/**
	* Input assembly state descriptor
	*/
	struct InputAssemblyStateDesc
	{
		types::EPrimitiveTopology topology = types::EPrimitiveTopology::TRIANGLE_LIST;
		bool primitiveRestartEnable = false;
	};
}
