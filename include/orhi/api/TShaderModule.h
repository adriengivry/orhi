/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/detail/Object.h>
#include <orhi/types/EGraphicsBackend.h>

#include <span>

namespace orhi::api
{
	template<typename BackendTraits> class TDevice;

	/**
	* @brief A compiled shader module for use in graphics pipelines
	* 
	* TShaderModule represents a compiled shader (vertex, fragment, compute, etc.)
	* that can be used as a stage in a graphics or compute pipeline. The shader
	* source code must be pre-compiled to the target backend's bytecode format.
	* 
	* @tparam BackendTraits Backend-specific traits defining implementation types
	*/
	template<typename BackendTraits>
	class TShaderModule final : public detail::Object
	{
	public:
		/**
		* @brief Creates a shader module from compiled bytecode
		* @param p_device Reference to the device that will own this shader module
		* @param p_source Compiled shader bytecode as a span of bytes
		*/
		TShaderModule(
			TDevice<BackendTraits>& p_device,
			const std::span<const std::byte> p_source
		);

		/**
		* @brief Destroys the shader module and releases associated resources
		*/
		~TShaderModule();

	private:
		BackendTraits::ShaderModuleContext m_context;
	};
}
