/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/api/TBackend.h>

namespace orhi::impl::mock
{
	struct BackendContext {};
	using Backend = api::TBackend<types::EGraphicsBackend::NONE, BackendContext>;
}
