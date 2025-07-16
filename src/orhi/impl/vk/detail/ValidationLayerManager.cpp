/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#if defined(ORHI_COMPILE_VULKAN)

#include <orhi/impl/vk/detail/ValidationLayerManager.h>

#include <iostream>

namespace orhi::impl::vk::detail
{
	ValidationLayerManager::ValidationLayerManager()
	{
		uint32_t layerCount = 0;
		vkEnumerateInstanceLayerProperties(&layerCount, nullptr);
		m_layers.resize(layerCount);
		vkEnumerateInstanceLayerProperties(&layerCount, m_layers.data());
	}

	bool ValidationLayerManager::IsValidationLayerSupported(const std::string_view p_layer) const
	{
		for (auto& currentLayer : m_layers)
		{
			if (strcmp(currentLayer.layerName, p_layer.data()) == 0)
			{
				return true;
			}
		}

		return false;
	}

	void ValidationLayerManager::LogValidationLayers() const
	{
		std::cout << m_layers.size() << " available layers:\n";

		for (const auto& layer : m_layers)
		{
			std::cout << '\t' << layer.layerName << '\n';
		}
	}

	std::vector<const char*> ValidationLayerManager::FilterValidationLayers(std::span<const RequestedValidationLayer> p_requestedLayers) const
	{
		std::vector<const char*> filteredValidationLayers;

		for (const auto& layer : p_requestedLayers)
		{
			if (!IsValidationLayerSupported(layer.name))
			{
				if (layer.required)
				{
					throw std::runtime_error("required validation layer not supported!");
				}
				else
				{
					std::cout << "Optional requested validation layer '" << layer.name << "' isn't supported: skipped\n";
				}
			}
			else
			{
				filteredValidationLayers.push_back(layer.name.c_str());
			}
		}

		return filteredValidationLayers;
	}
}

#endif // #if defined(ORHI_COMPILE_VULKAN)
