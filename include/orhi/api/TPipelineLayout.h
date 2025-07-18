/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/data/PipelineLayoutDesc.h>
#include <orhi/impl/common/BackendObject.h>
#include <orhi/types/EGraphicsBackend.h>

namespace orhi::api
{
	template<typename BackendTraits> class TDevice;

	/**
	* @brief A pipeline layout defining the interface between shader stages and resources
	* 
	* TPipelineLayout defines the complete resource interface for a pipeline,
	* including descriptor set layouts and push constant ranges. It serves as a
	* contract between the application and the graphics pipeline, specifying what
	* resources the pipeline expects to receive.
	* 
	* @tparam BackendTraits Backend-specific traits defining implementation types
	*/
	template<typename BackendTraits>
	class TPipelineLayout final : public impl::common::BackendObject
	{
	public:
		/**
		* @brief Creates a pipeline layout with the specified descriptor set layouts
		* @param p_device Reference to the device that will own this pipeline layout
		* @param p_desc Pipeline layout descriptor specifying layouts and push constants
		*/
		TPipelineLayout(
			TDevice<BackendTraits>& p_device,
			const data::PipelineLayoutDesc<BackendTraits>& p_desc = {}
		);

		/**
		* @brief Destroys the pipeline layout and releases associated resources
		*/
		~TPipelineLayout();

	private:
		BackendTraits::PipelineLayoutContext m_context;
	};
}
