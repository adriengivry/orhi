/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#if defined(ORHI_COMPILE_VULKAN)

#include <vulkan/vulkan.h>

#include <span>
#include <string>
#include <vector>

namespace orhi::impl::vk::detail
{
	struct RequestedValidationLayer
	{
		std::string name;
		bool required;
	};

	class ValidationLayerManager
	{
	public:
		/**
		* Creates the validation layer manager, and automatically fetches supported layers
		*/
		ValidationLayerManager();

		/**
		* Destroys the validation layer manager
		*/
		virtual ~ValidationLayerManager() = default;

		/**
		* Returns true if a given validation layer is supported
		*/
		bool IsValidationLayerSupported(const std::string_view layer) const;

		/**
		* Prints the given list of validation layers to the console
		*/
		void LogValidationLayers() const;

		/**
		* Returns a formatted list of available validation layers, skipping any unsupported validation layer,
		* and returning an error if a required validation layer isn't available
		*/
		std::vector<const char*> FilterValidationLayers(std::span<const RequestedValidationLayer> p_requestedLayers) const;

	private:
		std::vector<VkLayerProperties> m_layers;
	};
}

#endif // #if defined(ORHI_COMPILE_VULKAN)
