/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/types/EGraphicsBackend.h>
#include <orhi/apii/TFramebuffer.h>
#include <vector>

namespace orhi::apii
{
	template<types::EGraphicsBackend Backend, class Context, class FramebufferContext>
	class TSwapChain final
	{
	public:
		/**
		* Create a swap chain for the given window size
		* @param p_windowSize
		*/
		TSwapChain(std::pair<uint32_t, uint32_t> p_windowSize);

		/**
		* Create framebuffers for each image in the swap chain, for a given render pass
		*/
		std::vector<orhi::apii::TFramebuffer<Backend, FramebufferContext>> CreateFramebuffers(/* TODO ADD RENDER PASS PARAM */);

	private:
		Context m_context;
	};
}
