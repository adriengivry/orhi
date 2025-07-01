/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#if defined(ORHI_COMPILE_VULKAN)

#include <orhi/debug/Assert.h>
#include <orhi/debug/Log.h>
#include <orhi/impl/vk/Backend.h>
#include <orhi/impl/vk/details/ExtensionManager.h>
#include <orhi/impl/vk/details/ValidationLayerManager.h>
#include <orhi/impl/vk/details/DebugMessenger.h>
#include <vulkan/vulkan.h>

using namespace orhi::impl::vk;

namespace
{
	std::unique_ptr<details::DebugMessenger> g_debugMessenger;
}

namespace orhi
{
	template<>
	Backend::TBackend(
		const std::vector<std::string>& p_extensions,
		bool p_debug
	)
	{
		details::ExtensionManager extensionManager;
		details::ValidationLayerManager validationLayerManager;

		extensionManager.FetchExtensions<details::EExtensionHandler::Instance>();

		extensionManager.LogExtensions();
		validationLayerManager.LogValidationLayers();

		const bool useDebugUtilsExtension =
			p_debug && 
			extensionManager.IsExtensionSupported(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);

		std::vector<details::RequestedExtension> requestedExtensions;

		// (optional) extension for message callback
		if (useDebugUtilsExtension)
		{
			requestedExtensions.emplace_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME, true);
		};

		for (auto& extension : p_extensions)
		{
			requestedExtensions.emplace_back(extension, true); // "true" to make it required
		}

		std::vector<details::RequestedValidationLayer> requestedValidationLayers;

		if (useDebugUtilsExtension)
		{
			requestedValidationLayers.emplace_back("VK_LAYER_KHRONOS_validation", false);
		}

		auto extensions = extensionManager.FilterExtensions(requestedExtensions);
		auto validationLayers = validationLayerManager.FilterValidationLayers(requestedValidationLayers);

		// VkApplicationInfo is optional, but useful to specify info about our app.
		VkApplicationInfo appInfo{
			.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
			.pNext = VK_NULL_HANDLE, // To pass additionnal information, e.g. for extensions
			.pApplicationName = "vulkan-sandbox",
			.applicationVersion = VK_MAKE_VERSION(1, 0, 0),
			.pEngineName = "No Engine",
			.engineVersion = VK_MAKE_VERSION(1, 0, 0),
			.apiVersion = VK_API_VERSION_1_0
		};

		VkInstanceCreateInfo createInfo{
			.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
			.pApplicationInfo = &appInfo,
			.enabledLayerCount = static_cast<uint32_t>(validationLayers.size()), // determine the global validation layers to enable
			.ppEnabledLayerNames = validationLayers.data(),
			.enabledExtensionCount = static_cast<uint32_t>(extensions.size()),
			.ppEnabledExtensionNames = extensions.data()
		};

		std::unique_ptr<VkDebugUtilsMessengerCreateInfoEXT> debugUtilsMessengerCreateInfo;

		// Since the debug messenger is created after the vkInstance is created, it won't catch issues
		// related to instance creation.
		// To fix that, we add an instance of VkDebugUtilsMessengerCreateInfoEXT to createInfo.pNext.
		if (useDebugUtilsExtension)
		{
			debugUtilsMessengerCreateInfo = std::make_unique<VkDebugUtilsMessengerCreateInfoEXT>(
				details::DebugMessengerUtil::GenerateCreateInfo()
			);

			createInfo.pNext = debugUtilsMessengerCreateInfo.get();
		}

		VkResult result = vkCreateInstance(
			&createInfo,
			nullptr,
			&m_context.instance
		);

		ORHI_ASSERT(result == VK_SUCCESS, "failed to create instance!");

		ORHI_LOG_INFO("Vulkan instance created successfully!");

		// If the debug utils extension is being used, setup the debug messenger
		if (useDebugUtilsExtension)
		{
			g_debugMessenger = std::make_unique<details::DebugMessenger>(m_context.instance, *debugUtilsMessengerCreateInfo);
		}
	}

	Backend::~TBackend()
	{
		g_debugMessenger.reset();
		vkDestroyInstance(m_context.instance, nullptr);
	}
}

#endif // #if defined(ORHI_COMPILE_VULKAN)
