/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/data/NativeHandle.h>
#include <orhi/types/EFormat.h>
#include <orhi/types/EGraphicsBackend.h>

namespace orhi::api
{
	template<typename BackendTraits> class TDevice;

	/**
	* @brief A render pass defining the structure of rendering operations
	* 
	* TRenderPass defines the attachments, subpasses, and dependencies for
	* a rendering operation. It specifies the format and usage of color,
	* depth, and stencil attachments used during rendering.
	* 
	* @tparam BackendTraits Backend-specific traits defining implementation types
	*/
	template<typename BackendTraits>
	class TRenderPass final
	{
	public:
		/**
		* @brief Creates a render pass with a single color attachment
		* @param p_device Reference to the device that will own this render pass
		* @param p_format Format of the color attachment
		*/
		TRenderPass(
			TDevice<BackendTraits>& p_device,
			types::EFormat p_format
		);

		/**
		* @brief Destroys the render pass and releases associated resources
		*/
		~TRenderPass();

		/**
		* @brief Gets the native handle for backend-specific operations
		* @return Native handle to the underlying render pass object
		*/
		data::NativeHandle GetNativeHandle() const;

	private:
		BackendTraits::RenderPassContext m_context;
	};
}
