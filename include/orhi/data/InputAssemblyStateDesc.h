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
	* @brief Input assembly state descriptor for graphics pipelines
	* 
	* Defines how vertex data is assembled into primitives (points, lines, triangles)
	* and whether primitive restart is enabled for indexed drawing operations.
	*/
	struct InputAssemblyStateDesc
	{
		types::EPrimitiveTopology topology = types::EPrimitiveTopology::TRIANGLE_LIST;
		bool primitiveRestartEnable = false;
	};
}
