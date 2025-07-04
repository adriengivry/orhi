/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#include <orhi/impl/vk/details/DebugMessenger.h>
#include <stdexcept>

namespace
{
	auto getMessageOutputStream(VkDebugUtilsMessageSeverityFlagBitsEXT severity)
	{
		switch (severity)
		{
		case VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT: return stdout;
		case VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT: return stdout;
		case VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT: return stdout;
		case VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT: return stderr;
		}

		return stdout;
	}

	std::string getMessageSeverityHeader(VkDebugUtilsMessageSeverityFlagBitsEXT severity)
	{
		switch (severity)
		{
		case VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT: return "[vk verbose]";
		case VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT: return "[vk info]";
		case VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT: return "[vk warning]";
		case VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT: return "[vk error]";
		}

		return "[vk unknown]";
	}

	std::string getMessageTypeHeader(VkDebugUtilsMessageTypeFlagsEXT type)
	{
		switch (type)
		{
		case VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT: return "<general>";
		case VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT: return "<performance>";
		case VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT: return "<validation>";
		}

		return "<unknown>";
	}

	/**
	* Returns a boolean that indicates if the Vulkan call that triggered the validation layer message should be aborted.
	* If the callback returns true, then the call is aborted with the VK_ERROR_VALIDATION_FAILED_EXT error.
	* This is normally only used to test the validation layers themselves, so you should always return VK_FALSE.
	*/
	static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
		VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
		VkDebugUtilsMessageTypeFlagsEXT messageType,
		const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
		void* pUserData
	)
	{
		// Ignore info messages (too noisy).
		// Could also be achieved by not using "VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT" when 
		// creating the DebugUtilsMessageCreateInfo instance
		if (messageSeverity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT)
		{
			return VK_FALSE;
		}

		const auto stream = getMessageOutputStream(messageSeverity);
		const std::string severityHeader = getMessageSeverityHeader(messageSeverity);
		const std::string typeHeader = getMessageTypeHeader(messageType);
		const std::string message = pCallbackData->pMessage;

		fprintf(
			stream,
			"%s %s: %s\n",
			severityHeader.data(),
			typeHeader.data(),
			message.data()
		);

		return VK_FALSE;
	}

	// Unfortunately, because this function is an extension function, it is not automatically loaded.
	// We have to look up its address ourselves using vkGetInstanceProcAddr.
	// We're going to create our own proxy function that handles this in the background
	VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger)
	{
		auto func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");

		if (func != nullptr)
		{
			return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
		}
		else
		{
			return VK_ERROR_EXTENSION_NOT_PRESENT;
		}
	}

	// Same as above, since this is an extension function, it is not automatically loaded.
	void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator)
	{
		auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");

		if (func != nullptr)
		{
			func(instance, debugMessenger, pAllocator);
		}
	}
}

namespace orhi::impl::vk::details
{
	VkDebugUtilsMessengerCreateInfoEXT DebugMessengerUtil::GenerateCreateInfo()
	{
		return {
			.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT,
			.messageSeverity =
				VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT |
				VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT | // could be removed to get less noise
				VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
				VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT,
			.messageType =
				VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
				VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
				VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT,
			.pfnUserCallback = debugCallback,
			.pUserData = nullptr // Optional
		};
	}

	DebugMessenger::DebugMessenger(
		VkInstance p_instance,
		const VkDebugUtilsMessengerCreateInfoEXT& p_createInfo
	) :
		m_instance(p_instance)
	{
		if (CreateDebugUtilsMessengerEXT(
			m_instance,
			&p_createInfo,
			nullptr,
			&m_handle
		) != VK_SUCCESS)
		{
			throw std::runtime_error("failed to set up debug messenger!");
		}
	}

	DebugMessenger::~DebugMessenger()
	{
		DestroyDebugUtilsMessengerEXT(m_instance, m_handle, nullptr);
	}
}
