/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/types/EGraphicsBackend.h>
#include <orhi/api/TFramebuffer.h>
#include <orhi/api/TRenderPass.h>
#include <orhi/api/TSemaphore.h>
#include <orhi/api/TFence.h>
#include <vector>
#include <optional>

namespace orhi::api
{
	template<types::EGraphicsBackend Backend, class Context, class DeviceContext, class FramebufferContext, class RenderPassContext, class SemaphoreContext, class FenceContext>
	class TSwapChain final
	{
	public:
		/**
		* Create a swap chain for the given window size
		* @param p_device
		* @param p_surface
		* @param p_windowSize
		* @param p_desc
		* @param p_oldSwapChain
		*/
		TSwapChain(
			TDevice<Backend, DeviceContext>& p_device,
			data::NativeHandle p_surface,
			std::pair<uint32_t, uint32_t> p_windowSize,
			const data::SwapChainDesc& p_desc,
			std::optional<std::reference_wrapper<TSwapChain<
				Backend,
				Context,
				DeviceContext,
				FramebufferContext,
				RenderPassContext,
				SemaphoreContext,
				FenceContext
			>>> p_oldSwapChain = std::nullopt
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
		* Returns the index of the next image
		* @note throw an exception if the swapchain is out of date
		*/
		uint32_t AcquireNextImage(
			std::optional<std::reference_wrapper<TSemaphore<Backend, SemaphoreContext, DeviceContext>>> p_semaphore = std::nullopt,
			std::optional<std::reference_wrapper<TFence<Backend, FenceContext, DeviceContext>>> p_fence = std::nullopt,
			std::optional<uint64_t> p_timeout = std::nullopt
		);

		/**
		* Returns the underlying object's native handle
		*/
		data::NativeHandle GetNativeHandle() const;

	private:
		Context m_context;
	};
}
