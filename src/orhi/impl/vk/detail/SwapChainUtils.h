/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#if defined(ORHI_COMPILE_VULKAN)

#include <vulkan/vulkan.h>

#include <vector>

namespace orhi::impl::vk::detail
{
	struct SwapChainSupportDetails
	{
		VkSurfaceCapabilitiesKHR capabilities;
		std::vector<VkSurfaceFormatKHR> formats;
		std::vector<VkPresentModeKHR> presentModes;
	};

	struct SwapChainOptimalConfig
	{
		VkSurfaceCapabilitiesKHR capabilities;
		VkSurfaceFormatKHR surfaceFormat;
		VkPresentModeKHR presentMode;
		VkExtent2D extent;
	};

	class SwapChainUtils
	{
	public:
		/**
		* Returns swap chain support details for a given physical device and a surface
		*/
		static SwapChainSupportDetails QuerySwapChainDetails(VkPhysicalDevice device, VkSurfaceKHR p_surface);

		/**
		* Create optimal swap chain config (input for swap chain creation)
		*/
		static SwapChainOptimalConfig CalculateSwapChainOptimalConfig(const SwapChainSupportDetails& p_details, VkExtent2D p_windowExtent);
	};
}

#endif // #if defined(ORHI_COMPILE_VULKAN)
