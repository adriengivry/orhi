/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/data/GraphicsPipelineDesc.h>
#include <orhi/data/NativeHandle.h>
#include <orhi/types/EGraphicsBackend.h>

namespace orhi::api
{
	template<typename BackendTraits> class TDevice;

	/**
	* @brief A graphics pipeline defining the complete rendering state
	* 
	* TGraphicsPipeline encapsulates all fixed-function and programmable stages
	* of the graphics pipeline, including shaders, vertex input, rasterization,
	* and output blending state. Once created, pipelines are immutable.
	* 
	* @tparam BackendTraits Backend-specific traits defining implementation types
	*/
	template<typename BackendTraits>
	class TGraphicsPipeline final
	{
	public:
		/**
		* @brief Creates a graphics pipeline with the specified configuration
		* @param p_device Reference to the device that will own this graphics pipeline
		* @param p_desc Graphics pipeline descriptor specifying shaders, state, and layout
		*/
		TGraphicsPipeline(
			TDevice<BackendTraits>& p_device,
			const data::GraphicsPipelineDesc<BackendTraits>& p_desc
		);

		/**
		* @brief Destroys the graphics pipeline and releases associated resources
		*/
		~TGraphicsPipeline();

		/**
		* @brief Gets the native handle to the pipeline layout
		* @return Native handle to the underlying pipeline layout object
		*/
		data::NativeHandle GetLayoutHandle() const;

		/**
		* @brief Gets the native handle for backend-specific operations
		* @return Native handle to the underlying graphics pipeline object
		*/
		data::NativeHandle GetNativeHandle() const;

	private:
		BackendTraits::GraphicsPipelineContext m_context;
	};
}
