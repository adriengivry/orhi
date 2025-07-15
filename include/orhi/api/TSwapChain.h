/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/data/NativeHandle.h>
#include <orhi/data/SwapChainDesc.h>
#include <orhi/math/Extent2D.h>
#include <orhi/types/EGraphicsBackend.h>

#include <optional>
#include <span>
#include <vector>

namespace orhi::api
{
	template<typename BackendTraits> class TDescriptor;
	template<typename BackendTraits> class TDevice;
	template<typename BackendTraits> class TFence;
	template<typename BackendTraits> class TFramebuffer;
	template<typename BackendTraits> class TRenderPass;
	template<typename BackendTraits> class TSemaphore;

	/**
	* @brief A swap chain for presenting rendered images to the screen
	* 
	* TSwapChain manages a collection of images that can be rendered to and
	* presented to the display. It handles double/triple buffering and
	* synchronization with the display refresh rate.
	* 
	* @tparam BackendTraits Backend-specific traits defining implementation types
	*/
	template<typename BackendTraits>
	class TSwapChain final
	{
	public:
		/**
		* @brief Creates a swap chain for the specified surface and window size
		* @param p_device Reference to the device that will own this swap chain
		* @param p_surface Native handle to the presentation surface
		* @param p_windowSize Window dimensions
		* @param p_desc Swap chain descriptor specifying format, present mode, and other properties
		* @param p_oldSwapChain Optional reference to an old swap chain for resource reuse during recreation
		*/
		TSwapChain(
			TDevice<BackendTraits>& p_device,
			data::NativeHandle p_surface,
			const math::Extent2D& p_windowSize,
			const data::SwapChainDesc& p_desc,
			std::optional<std::reference_wrapper<TSwapChain<BackendTraits>>> p_oldSwapChain = std::nullopt
		);

		/**
		* @brief Destroys the swap chain and releases associated resources
		*/
		~TSwapChain();

		/**
		* @brief Returns the number of images in the swap chain
		* @return Number of images available for rendering
		*/
		uint32_t GetImageCount() const;

		/**
		* @brief Gets the descriptor for a specific swap chain image
		* @return Reference to the descriptor for the specified image index
		*/
		TDescriptor<BackendTraits>& GetImageDescriptor(uint32_t p_index);

		/**
		* @brief Acquires the index of the next available swap chain image
		* @param p_semaphore Optional semaphore to signal when the image is available
		* @param p_fence Optional fence to signal when the image is available
		* @param p_timeout Optional timeout in nanoseconds for the acquisition
		* @return Index of the acquired image
		* @throws Exception if the swap chain is out of date and needs recreation
		*/
		uint32_t AcquireNextImage(
			std::optional<std::reference_wrapper<TSemaphore<BackendTraits>>> p_semaphore = std::nullopt,
			std::optional<std::reference_wrapper<TFence<BackendTraits>>> p_fence = std::nullopt,
			std::optional<uint64_t> p_timeout = std::nullopt
		);

		/**
		* @brief Gets the native handle for backend-specific operations
		* @return Native handle to the underlying swap chain object
		*/
		data::NativeHandle GetNativeHandle() const;

	private:
		BackendTraits::SwapChainContext m_context;
	};
}
