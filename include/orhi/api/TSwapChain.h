/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/data/NativeHandle.h>
#include <orhi/data/SwapChainDesc.h>
#include <orhi/types/EGraphicsBackend.h>

#include <vector>
#include <optional>

namespace orhi::api
{
	template<typename BackendTraits> class TDevice;
	template<typename BackendTraits> class TFence;
	template<typename BackendTraits> class TFramebuffer;
	template<typename BackendTraits> class TRenderPass;
	template<typename BackendTraits> class TSemaphore;

	template<typename BackendTraits>
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
			TDevice<BackendTraits>& p_device,
			data::NativeHandle p_surface,
			std::pair<uint32_t, uint32_t> p_windowSize,
			const data::SwapChainDesc& p_desc,
			std::optional<std::reference_wrapper<TSwapChain<BackendTraits>>> p_oldSwapChain = std::nullopt
		);

		/**
		* Destroys the swap chain
		*/
		~TSwapChain();

		/**
		* Create framebuffers for each image in the swap chain, for a given render pass
		*/
		std::vector<orhi::api::TFramebuffer<BackendTraits>> CreateFramebuffers(
			TRenderPass<BackendTraits>& p_renderPass
		);

		/**
		* Returns the index of the next image
		* @note throw an exception if the swapchain is out of date
		*/
		uint32_t AcquireNextImage(
			std::optional<std::reference_wrapper<TSemaphore<BackendTraits>>> p_semaphore = std::nullopt,
			std::optional<std::reference_wrapper<TFence<BackendTraits>>> p_fence = std::nullopt,
			std::optional<uint64_t> p_timeout = std::nullopt
		);

		/**
		* Returns the underlying object's native handle
		*/
		data::NativeHandle GetNativeHandle() const;

	private:
		BackendTraits::SwapChainContext m_context;
	};
}
