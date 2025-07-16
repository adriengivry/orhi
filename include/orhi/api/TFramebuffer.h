/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/data/FramebufferDesc.h>
#include <orhi/detail/Object.h>
#include <orhi/types/EGraphicsBackend.h>

namespace orhi::api
{
	template<typename BackendTraits> class TDevice;

	/**
	* @brief A framebuffer object containing render targets
	* 
	* TFramebuffer represents a collection of attachments (color, depth, stencil)
	* that serve as render targets during rendering operations. Framebuffers must
	* be compatible with the render pass they are used with.
	* 
	* @tparam BackendTraits Backend-specific traits defining implementation types
	*/
	template<typename BackendTraits>
	class TFramebuffer final : public detail::Object
	{
	public:
		/**
		* @brief Creates a framebuffer with the specified attachments
		* @param p_device Reference to the device that will own this framebuffer
		* @param p_desc Framebuffer descriptor specifying attachments, render pass, and dimensions
		*/
		TFramebuffer(
			TDevice<BackendTraits>& p_device,
			const data::FramebufferDesc<BackendTraits>& p_desc
		);

		/**
		* @brief Destroys the framebuffer and releases associated resources
		*/
		~TFramebuffer();

	private:
		BackendTraits::FramebufferContext m_context;
	};
}
