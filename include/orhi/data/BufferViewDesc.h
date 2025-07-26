/**
* @project: orhi (OpenRHI)
* @author: Jian Bang Xu
* @licence: MIT
*/

#pragma once

#include <orhi/impl/common/NativeHandle.h>
#include <orhi/types/EFormat.h>

namespace orhi::data
{
	/**
	* @brief Descriptor for buffer view creation
	*
	* Defines how a buffer should be viewed and accessed by shaders,
	* including the target buffer, format interpretation,
	*
	* @tparam BackendTraits Backend-specific traits defining implementation types
	*/
	struct BufferViewDesc
	{
		impl::common::NativeHandle buffer;
		types::EFormat format = types::EFormat::R32_UINT;
	};
}
