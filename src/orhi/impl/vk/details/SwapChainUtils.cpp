/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#include <orhi/impl/vk/details/SwapChainUtils.h>
#include <orhi/debug/Assert.h>
#include <algorithm>

namespace
{
	VkSurfaceFormatKHR ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& p_availableFormats)
	{
		constexpr auto k_preferredFormat = VK_FORMAT_B8G8R8A8_SRGB;
		constexpr auto k_preferredColorSpace = VK_COLOR_SPACE_SRGB_NONLINEAR_KHR;

		for (const auto& availableFormat : p_availableFormats)
		{
			if (availableFormat.format == k_preferredFormat && availableFormat.colorSpace == k_preferredColorSpace)
			{
				return availableFormat;
			}
		}

		return p_availableFormats.front();
	}

	VkPresentModeKHR ChooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes)
	{
		// Very nice trade-off if energy usage is not a concern.
		// It allows us to avoid tearing while still maintaining a fairly low latency by rendering
		// new images that are as up-to-date as possible right until the vertical blank.
		// On mobile devices, where energy usage is more important, you will probably want to use VK_PRESENT_MODE_FIFO_KHR instead.
		constexpr auto k_preferredPresentMode = VK_PRESENT_MODE_MAILBOX_KHR;

		for (const auto& availablePresentMode : availablePresentModes)
		{
			if (availablePresentMode == k_preferredPresentMode)
			{
				return availablePresentMode;
			}
		}

		// Only the VK_PRESENT_MODE_FIFO_KHR mode is guaranteed to be available, so we can use it as a fallback solution.
		return VK_PRESENT_MODE_FIFO_KHR;
	}

	// From https://vulkan-tutorial.com/Drawing_a_triangle/Presentation/Swap_chain:
	// The swap extent is the resolution of the swap chain images and it's almost always exactly equal to the
	// resolution of the window that we're drawing to in pixels (more on that in a moment).
	// The range of the possible resolutions is defined in the VkSurfaceCapabilitiesKHR structure.
	// Vulkan tells us to match the resolution of the window by setting the width and height in the currentExtent member.
	// However, some window managers do allow us to differ here and this is indicated by setting the width and height
	// in currentExtent to a special value: the maximum value of uint32_t.
	// In that case we'll pick the resolution that best matches the window within the minImageExtent and maxImageExtent bounds.
	// But we must specify the resolution in the correct unit.
	VkExtent2D ChooseSwapExtent(const VkSurfaceCapabilitiesKHR& p_capabilities, VkExtent2D p_windowExtent)
	{
		if (p_capabilities.currentExtent.width != std::numeric_limits<uint32_t>::max())
		{
			return p_capabilities.currentExtent;
		}
		else
		{
			// Make sure to keep the extent within the capabilities of the device
			return {
				std::clamp(p_windowExtent.width, p_capabilities.minImageExtent.width, p_capabilities.maxImageExtent.width),
				std::clamp(p_windowExtent.height, p_capabilities.minImageExtent.height, p_capabilities.maxImageExtent.height)
			};
		}
	}
}

namespace orhi::impl::vk::details
{
	SwapChainSupportDetails SwapChainUtils::QuerySwapChainDetails(VkPhysicalDevice p_device, VkSurfaceKHR p_surface)
	{
		SwapChainSupportDetails details;

		uint32_t formatCount;
		vkGetPhysicalDeviceSurfaceFormatsKHR(p_device, p_surface, &formatCount, nullptr);

		// TODO: This pattern where we skip the second invocation of vkGetPhysicalDeviceSurfaceFormatsKHR if the count is 0,
		// could be reused for extensions, layers, and queue families, etc.
		if (formatCount != 0)
		{
			details.formats.resize(formatCount);
			vkGetPhysicalDeviceSurfaceFormatsKHR(p_device, p_surface, &formatCount, details.formats.data());
		}

		uint32_t presentModeCount;
		vkGetPhysicalDeviceSurfacePresentModesKHR(p_device, p_surface, &presentModeCount, nullptr);

		if (presentModeCount != 0)
		{
			details.presentModes.resize(presentModeCount);
			vkGetPhysicalDeviceSurfacePresentModesKHR(p_device, p_surface, &presentModeCount, details.presentModes.data());
		}

		VkResult capabilityQueryResult = vkGetPhysicalDeviceSurfaceCapabilitiesKHR(
			p_device,
			p_surface,
			&details.capabilities
		);

		ORHI_ASSERT(capabilityQueryResult == VK_SUCCESS, "failed to retrieve device's capabilities.");

		return details;
	}

	SwapChainOptimalConfig SwapChainUtils::CalculateSwapChainOptimalConfig(const SwapChainSupportDetails& p_details, VkExtent2D p_windowExtent)
	{
		return SwapChainOptimalConfig{
			.capabilities = p_details.capabilities,
			.surfaceFormat = ChooseSwapSurfaceFormat(p_details.formats),
			.presentMode = ChooseSwapPresentMode(p_details.presentModes),
			.extent = ChooseSwapExtent(p_details.capabilities, p_windowExtent)
		};
	}
}
