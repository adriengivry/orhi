/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/types/EGraphicsBackend.h>
#include <orhi/api/TFramebuffer.h>
#include <orhi/api/TRenderPass.h>
#include <vector>

namespace orhi::api
{
	template<types::EGraphicsBackend Backend, class Context, class DeviceContext, class FramebufferContext, class RenderPassContext>
	class TSwapChain final
	{
	public:
		/**
		* Create a swap chain for the given window size
		* @param p_device
		* @param p_surface
		* @param p_windowSize
		* @param p_desc
		*/
		TSwapChain(
			TDevice<Backend, DeviceContext>& p_device,
			data::NativeHandle p_surface,
			std::pair<uint32_t, uint32_t> p_windowSize,
			const data::SwapChainDesc& p_desc
		);

		/**
		* Destroys the swap chain
		*/
		~TSwapChain();

		/**
		* Create framebuffers for each image in the swap chain, for a given render pass
		*/
		std::vector<orhi::api::TFramebuffer<Backend, FramebufferContext, DeviceContext, RenderPassContext>> CreateFramebuffers(
			TRenderPass<Backend, RenderPassContext, DeviceContext>& p_renderPass
		);

		/**
		* Returns the underlying object's native handle
		*/
		data::NativeHandle GetNativeHandle() const;

	private:
		Context m_context;
	};
}
