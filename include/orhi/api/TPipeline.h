/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/data/ComputePipelineDesc.h>
#include <orhi/data/GraphicsPipelineDesc.h>
#include <orhi/impl/common/BackendObject.h>
#include <orhi/types/EGraphicsBackend.h>

namespace orhi::api
{
	template<typename BackendTraits> class TDevice;

	/**
	* @brief A generic pipeline object for graphics and compute operations
	* 
	* TPipeline encapsulates the functionality of both graphics and compute pipelines,
	* allowing for the creation and management of pipelines in a backend-agnostic manner.
	* It provides methods to create pipelines with specified configurations.
	* 
	* @tparam BackendTraits Backend-specific traits defining implementation types
	*/
	template<typename BackendTraits>
	class TPipeline final : public impl::common::BackendObject
	{
	public:
		/**
		* @brief Creates a graphics pipeline with the specified configuration
		* @param p_device Reference to the device that will own this graphics pipeline
		* @param p_desc Graphics pipeline descriptor specifying shaders, state, and layout
		*/
		TPipeline(
			TDevice<BackendTraits>& p_device,
			const data::GraphicsPipelineDesc<BackendTraits>& p_desc
		);

		/**
		* @brief Creates a compute pipeline with the specified configuration
		* @param p_device Reference to the device that will own this compute pipeline
		* @param p_desc Compute pipeline descriptor specifying shaders, state, and layout
		*/
		TPipeline(
			TDevice<BackendTraits>& p_device,
			const data::ComputePipelineDesc<BackendTraits>& p_desc
		);

		/**
		* @brief Destroys the pipeline and releases associated resources
		*/
		~TPipeline();

		/**
		* @brief Gets the native handle to the pipeline layout
		* @return Native handle to the underlying pipeline layout object
		*/
		impl::common::NativeHandle GetLayoutHandle() const;

	private:
		BackendTraits::PipelineContext m_context;
	};
}
