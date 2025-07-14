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

namespace orhi::impl::vk::details
{
	class DebugMessengerUtil
	{
	public:
		static VkDebugUtilsMessengerCreateInfoEXT GenerateCreateInfo();
	};

	class DebugMessenger
	{
	public:
		/**
		* Creates a debug messenger.
		*/
		DebugMessenger(VkInstance p_instance, const VkDebugUtilsMessengerCreateInfoEXT& p_createInfo);

		/**
		* Destroys the debug messenger
		*/
		virtual ~DebugMessenger();

	private:
		VkInstance m_instance;
		VkDebugUtilsMessengerEXT m_handle;
	};
}

#endif // #if defined(ORHI_COMPILE_VULKAN)
