/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#if defined(ORHI_COMPILE_VULKAN)

#if defined(_WIN32) || defined(_WIN64)
#define VK_USE_PLATFORM_WIN32_KHR
#endif

#include <orhi/debug/Assert.h>
#include <orhi/debug/Log.h>
#include <orhi/impl/vk/Backend.h>
#include <orhi/impl/vk/details/ExtensionManager.h>
#include <orhi/impl/vk/details/ValidationLayerManager.h>
#include <orhi/impl/vk/details/DebugMessenger.h>
#include <format>
#include <optional>
#include <set>
#include <vulkan/vulkan.h>

using namespace orhi::impl::vk;

namespace
{
	struct QueueFamilyIndices
	{
		std::optional<uint32_t> graphicsFamily;
		std::optional<uint32_t> presentFamily;

		bool IsComplete() const { return graphicsFamily && presentFamily; }

		std::vector<uint32_t> GetUniqueQueueIndices() const
		{
			ORHI_ASSERT(IsComplete(), "Incomplete queue family indices");

			std::set<uint32_t> uniqueIndices{
				graphicsFamily.value(),
				presentFamily.value()
			};

			std::vector<uint32_t> output;
			output.reserve(uniqueIndices.size());

			for (uint32_t index : uniqueIndices)
			{
				output.push_back(index);
			}

			return output;
		}
	};

	struct SwapChainSupportDetails
	{
		VkSurfaceCapabilitiesKHR capabilities;
		std::vector<VkSurfaceFormatKHR> formats;
		std::vector<VkPresentModeKHR> presentModes;
	};

	struct Device
	{
		VkPhysicalDevice physicalDevice;
		VkPhysicalDeviceProperties properties;
		VkPhysicalDeviceFeatures features;
		details::ExtensionManager extensionManager;
		QueueFamilyIndices queueFamilyIndices;
		orhi::data::DeviceInfo info;
		SwapChainSupportDetails swapChainSupportDetails;
	};

	std::unique_ptr<details::DebugMessenger> g_debugMessenger;
	std::vector<Device> g_devices;
	std::vector<orhi::data::DeviceInfo> g_suitableDeviceInfos;
	std::vector<details::RequestedExtension> g_deviceRequestedExtensions;

	SwapChainSupportDetails QuerySwapChainDetails(VkPhysicalDevice device, VkSurfaceKHR p_surface)
	{
		SwapChainSupportDetails details;

		vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, p_surface, &details.capabilities);

		uint32_t formatCount;
		vkGetPhysicalDeviceSurfaceFormatsKHR(device, p_surface, &formatCount, nullptr);

		// TODO: This pattern where we skip the second invocation of vkGetPhysicalDeviceSurfaceFormatsKHR if the count is 0,
		// could be reused for extensions, layers, and queue families, etc.
		if (formatCount != 0)
		{
			details.formats.resize(formatCount);
			vkGetPhysicalDeviceSurfaceFormatsKHR(device, p_surface, &formatCount, details.formats.data());
		}

		uint32_t presentModeCount;
		vkGetPhysicalDeviceSurfacePresentModesKHR(device, p_surface, &presentModeCount, nullptr);

		if (presentModeCount != 0)
		{
			details.presentModes.resize(presentModeCount);
			vkGetPhysicalDeviceSurfacePresentModesKHR(device, p_surface, &presentModeCount, details.presentModes.data());
		}

		return details;
	}

	bool IsSwapChainAdequate(const SwapChainSupportDetails& p_swapChainSupportDetails)
	{
		return
			!p_swapChainSupportDetails.formats.empty() &&
			!p_swapChainSupportDetails.presentModes.empty();
	}

	bool IsDeviceSuitable(Device& p_device, VkSurfaceKHR p_surface)
	{
		if (!p_device.queueFamilyIndices.IsComplete())
		{
			return false;
		}

		// A device isn't suitable if any of the required extension is unavailable
		for (auto& extension : g_deviceRequestedExtensions)
		{
			if (extension.required && !p_device.extensionManager.IsExtensionSupported(extension.name))
			{
				return false;
			}
		}

		// Store swap chain support details since they can be used for swap chain creation
		p_device.swapChainSupportDetails = QuerySwapChainDetails(p_device.physicalDevice, p_surface);

		if (!IsSwapChainAdequate(p_device.swapChainSupportDetails))
		{
			return false;
		}

		// For example, we can require a physical device to be a discrete GPU 
		return p_device.properties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU;
	}

	orhi::data::DeviceInfo GenerateDeviceInfo(VkPhysicalDevice device, VkSurfaceKHR p_surface)
	{
		static uint32_t deviceId = 0;

		return {
			.id = deviceId++
		};
	}

	QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice device, VkSurfaceKHR p_surface)
	{
		QueueFamilyIndices indices;

		uint32_t queueFamilyCount = 0;
		vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

		std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
		vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

		uint32_t i = 0;

		for (const auto& queueFamily : queueFamilies)
		{
			// Early exit if all family queues have been identified
			if (indices.IsComplete())
			{
				break;
			}

			if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT)
			{
				indices.graphicsFamily = i;
			}

			VkBool32 presentSupport = false;
			vkGetPhysicalDeviceSurfaceSupportKHR(device, i, p_surface, &presentSupport);
			if (presentSupport)
			{
				indices.presentFamily = i;
			}

			++i;
		}

		return indices;
	}
}

namespace orhi
{
	template<>
	Backend::TBackend(const data::BackendDesc& p_desc)
	{
		details::ExtensionManager extensionManager;
		details::ValidationLayerManager validationLayerManager;

		extensionManager.FetchExtensions<details::EExtensionHandler::Instance>();

		extensionManager.LogExtensions();
		validationLayerManager.LogValidationLayers();

		const bool useDebugUtilsExtension =
			p_desc.debug &&
			extensionManager.IsExtensionSupported(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);

		std::vector<details::RequestedExtension> requestedExtensions;

		// (optional) extension for message callback
		if (useDebugUtilsExtension)
		{
			requestedExtensions.emplace_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME, true);
		};

		for (auto& extension : p_desc.extensions)
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

		ORHI_ASSERT(p_desc.win32_windowHandle && p_desc.win32_instanceHandle, "incomplete surface desc");

#if defined(_WIN32) || defined(_WIN64)
		VkWin32SurfaceCreateInfoKHR surfaceCreateInfo{
			.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR,
			.hinstance = static_cast<HINSTANCE>(p_desc.win32_windowHandle),
			.hwnd = static_cast<HWND>(p_desc.win32_instanceHandle)
		};

		result = vkCreateWin32SurfaceKHR(
			m_context.instance,
			&surfaceCreateInfo,
			nullptr,
			&m_context.surface
		);

		ORHI_ASSERT(result == VK_SUCCESS, "failed to create window surface!");
#else
#error Other platforms than Windows aren't supported yet
#endif

		uint32_t deviceCount = 0;
		vkEnumeratePhysicalDevices(m_context.instance, &deviceCount, nullptr);

		ORHI_ASSERT(deviceCount > 0, "failed to find GPUs with Vulkan support!");

		std::vector<VkPhysicalDevice> physicalDevices(deviceCount);
		vkEnumeratePhysicalDevices(m_context.instance, &deviceCount, physicalDevices.data());

		for (VkPhysicalDevice physicalDevice : physicalDevices)
		{
			VkPhysicalDeviceProperties deviceProperties;
			vkGetPhysicalDeviceProperties(physicalDevice, &deviceProperties);

			VkPhysicalDeviceFeatures deviceFeatures;
			vkGetPhysicalDeviceFeatures(physicalDevice, &deviceFeatures);

			auto& device = g_devices.emplace_back(Device{
				.physicalDevice = physicalDevice,
				.properties = deviceProperties,
				.features = deviceFeatures,
				.extensionManager = {},
				.queueFamilyIndices = FindQueueFamilies(physicalDevice, m_context.surface),
				.info = GenerateDeviceInfo(physicalDevice, m_context.surface),
				.swapChainSupportDetails = {}
			});

			device.extensionManager.FetchExtensions<details::EExtensionHandler::PhysicalDevice>(device.physicalDevice);
		}

		g_suitableDeviceInfos.reserve(g_devices.size());

		g_deviceRequestedExtensions.emplace_back(
			VK_KHR_SWAPCHAIN_EXTENSION_NAME, true
		);

		for (Device& device : g_devices)
		{
			if (IsDeviceSuitable(device, m_context.surface))
			{
				ORHI_LOG_INFO(std::format("Suitable device found: {}", device.properties.deviceName));
				g_suitableDeviceInfos.emplace_back(device.info);
			}
		}
	}

	template<>
	Backend::~TBackend()
	{
		g_debugMessenger.reset();
		vkDestroyInstance(m_context.instance, nullptr);
	}

	template<>
	const std::vector<data::DeviceInfo>& Backend::GetSuitableDevices() const
	{
		return g_suitableDeviceInfos;
	}

	template<>
	void Backend::SelectDevice(uint32_t p_deviceIndex)
	{
		const Device& selectedDevice = [p_deviceIndex]() {
			for (const Device& device : g_devices)
			{
				if (device.info.id == p_deviceIndex)
				{
					return device;
				}
			}

			ORHI_ASSERT(false, "Provided device index doesn't correspond to any valid device");
			return g_devices[0];
		}();

		std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;

		VkPhysicalDevice physicalDevice = selectedDevice.physicalDevice;

		std::set<uint32_t> uniqueQueueFamilies = {
			selectedDevice.queueFamilyIndices.graphicsFamily.value(),
			selectedDevice.queueFamilyIndices.presentFamily.value()
		};

		float queuePriority = 1.0f;

		for (uint32_t queueFamily : uniqueQueueFamilies)
		{
			VkDeviceQueueCreateInfo queueCreateInfo{
				.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
				.queueFamilyIndex = queueFamily,
				.queueCount = 1,
				.pQueuePriorities = &queuePriority
			};

			queueCreateInfos.push_back(queueCreateInfo);
		}

		// Filter out all the non-supported extensions. All the required extensions should be available
		// since we checked for them in "IsSuitable()"
		std::vector<const char*> extensions = selectedDevice.extensionManager.FilterExtensions(g_deviceRequestedExtensions);

		VkDeviceCreateInfo createInfo{
			.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
			.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size()),
			.pQueueCreateInfos = queueCreateInfos.data(),
			// Deprecated validation layers on device
			// .enabledLayerCount = static_cast<uint32_t>(p_validationLayers.size()),
			// .ppEnabledLayerNames = p_validationLayers.data(),
			.enabledExtensionCount = static_cast<uint32_t>(extensions.size()),
			.ppEnabledExtensionNames = extensions.data(),
			.pEnabledFeatures = &selectedDevice.features,
		};

		if (vkCreateDevice(
			selectedDevice.physicalDevice,
			&createInfo,
			nullptr,
			&m_context.device
		) != VK_SUCCESS)
		{
			throw std::runtime_error("failed to create logical device!");
		}

		VkQueue graphicsQueue, presentQueue;
		vkGetDeviceQueue(m_context.device, selectedDevice.queueFamilyIndices.graphicsFamily.value(), 0, &graphicsQueue);
		vkGetDeviceQueue(m_context.device, selectedDevice.queueFamilyIndices.presentFamily.value(), 0, &presentQueue);
	}

	template<>
	bool Backend::Validate() const
	{
		return
			m_context.instance &&
			m_context.device &&
			m_context.surface;
	}
}

#endif // #if defined(ORHI_COMPILE_VULKAN)
