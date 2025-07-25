/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry, Jian Bang Xu
* @licence: MIT
*/

#pragma once

#include <orhi/api/TShaderModule.h>
#include <orhi/impl/dx12/BackendTraits.h>
#include <orhi/impl/dx12/Device.h>

namespace orhi::impl::dx12
{
	struct ShaderModuleContext
	{
		Device& device;
	};

	using ShaderModule = api::TShaderModule<BackendTraits>;
}
