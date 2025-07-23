/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#if defined(ORHI_COMPILE_VULKAN)

#if defined(ORHI_USE_WINDOW_SYSTEM_WIN32)
#define VK_USE_PLATFORM_WIN32_KHR
#elif defined(ORHI_USE_WINDOW_SYSTEM_XLIB)
#include <X11/Xlib.h>
#elif defined(ORHI_USE_WINDOW_SYSTEM_XCB)
#include <X11/Xlib-xcb.h>
#elif defined(ORHI_USE_WINDOW_SYSTEM_WAYLAND)
#include <wayland-client.h>
#elif defined(ORHI_USE_WINDOW_SYSTEM_COCOA)
#include <Cocoa/Cocoa.h>
#else
#error No supported window system selected
#endif

#include <orhi/impl/vk/Instance.h>

#include <orhi/debug/Assert.h>
#include <orhi/debug/Log.h>
#include <orhi/impl/vk/Device.h>
#include <orhi/impl/vk/detail/DebugMessenger.h>
#include <orhi/impl/vk/detail/DeviceCreationInfo.h>
#include <orhi/impl/vk/detail/ExtensionManager.h>
#include <orhi/impl/vk/detail/QueueFamilyIndices.h>
#include <orhi/impl/vk/detail/SwapChainUtils.h>
#include <orhi/impl/vk/detail/Types.h>
#include <orhi/impl/vk/detail/ValidationLayerManager.h>

#include <vulkan/vulkan.h>

#include <list>
#include <optional>
#include <set>

using namespace orhi::impl::vk;

namespace
{
	struct PhysicalDevice
	{
		VkPhysicalDevice physicalDevice;
		VkPhysicalDeviceProperties properties;
		VkPhysicalDeviceFeatures features;
		detail::ExtensionManager extensionManager;
		detail::QueueFamilyIndices queueFamilyIndices;
		orhi::data::DeviceInfo info;
		detail::SwapChainSupportDetails swapChainSupportDetails;
	};

	// Device creation
	std::vector<PhysicalDevice> g_physicalDevices;
	std::vector<orhi::data::DeviceInfo> g_suitableDeviceInfos;
	std::vector<detail::RequestedExtension> g_deviceRequestedExtensions;

	// Debug
	std::unique_ptr<detail::DebugMessenger> g_debugMessenger;

	// Actual logical devices
	std::list<Device> g_createdDevices;

	bool IsSwapChainAdequate(const detail::SwapChainSupportDetails& p_swapChainSupportDetails)
	{
		return
			!p_swapChainSupportDetails.formats.empty() &&
			!p_swapChainSupportDetails.presentModes.empty();
	}

	bool IsDeviceSuitable(PhysicalDevice& p_device, VkSurfaceKHR p_surface)
	{
		if (!p_device.queueFamilyIndices.IsComplete())
		{
			return false;
		}

		if (!p_device.features.samplerAnisotropy)
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
		p_device.swapChainSupportDetails = detail::SwapChainUtils::QuerySwapChainDetails(p_device.physicalDevice, p_surface);

		if (!IsSwapChainAdequate(p_device.swapChainSupportDetails))
		{
			return false;
		}

		// For example, we can require a physical device to be a discrete GPU 
		// return p_device.properties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU;

		return true;
	}

	VkSampleCountFlags GetMaxSampleCount(VkPhysicalDeviceProperties p_deviceProperties)
	{
		const VkSampleCountFlags counts =
			p_deviceProperties.limits.framebufferColorSampleCounts &
			p_deviceProperties.limits.framebufferDepthSampleCounts;

		if (counts & VK_SAMPLE_COUNT_64_BIT) { return VK_SAMPLE_COUNT_64_BIT; }
		if (counts & VK_SAMPLE_COUNT_32_BIT) { return VK_SAMPLE_COUNT_32_BIT; }
		if (counts & VK_SAMPLE_COUNT_16_BIT) { return VK_SAMPLE_COUNT_16_BIT; }
		if (counts & VK_SAMPLE_COUNT_8_BIT) { return VK_SAMPLE_COUNT_8_BIT; }
		if (counts & VK_SAMPLE_COUNT_4_BIT) { return VK_SAMPLE_COUNT_4_BIT; }
		if (counts & VK_SAMPLE_COUNT_2_BIT) { return VK_SAMPLE_COUNT_2_BIT; }

		return VK_SAMPLE_COUNT_1_BIT;
	}

	orhi::data::DeviceInfo GenerateDeviceInfo(
		VkPhysicalDevice device,
		VkPhysicalDeviceProperties properties,
		VkPhysicalDeviceFeatures features,
		VkSurfaceKHR p_surface
	)
	{
		static uint32_t deviceId = 0;

		return {
			.id = deviceId++,
			.maxSamplerAnisotropy = properties.limits.maxSamplerAnisotropy,
			.maxSampleCount = orhi::utils::ValueToEnum<orhi::types::ESampleCountFlags>(GetMaxSampleCount(properties))
		};
	}
}

namespace orhi
{
	template<>
	Instance::TInstance(const data::InstanceDesc& p_desc)
	{
		detail::ExtensionManager extensionManager;
		detail::ValidationLayerManager validationLayerManager;

		extensionManager.FetchExtensions<detail::EExtensionHandler::Instance>();

		extensionManager.LogExtensions();
		validationLayerManager.LogValidationLayers();

		const bool useDebugUtilsExtension =
			p_desc.debug &&
			extensionManager.IsExtensionSupported(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);

		std::vector<detail::RequestedExtension> requestedExtensions;

		// (optional) extension for message callback
		if (useDebugUtilsExtension)
		{
			requestedExtensions.emplace_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME, true);
		};

		for (auto& extension : p_desc.extensions)
		{
			requestedExtensions.emplace_back(extension, true); // "true" to make it required
		}

#if defined(ORHI_USE_WINDOW_SYSTEM_WIN32)
		requestedExtensions.emplace_back(VK_KHR_WIN32_SURFACE_EXTENSION_NAME, true);
#elif defined(ORHI_USE_WINDOW_SYSTEM_XLIB)
		requestedExtensions.emplace_back(VK_KHR_XLIB_SURFACE_EXTENSION_NAME, true);
#elif defined(ORHI_USE_WINDOW_SYSTEM_XCB)
		requestedExtensions.emplace_back(VK_KHR_XCB_SURFACE_EXTENSION_NAME, true);
#elif defined(ORHI_USE_WINDOW_SYSTEM_WAYLAND)
		requestedExtensions.emplace_back(VK_KHR_WAYLAND_SURFACE_EXTENSION_NAME, true);
#elif defined(ORHI_USE_WINDOW_SYSTEM_COCOA)
		requestedExtensions.emplace_back(VK_EXT_METAL_SURFACE_EXTENSION_NAME, true);
#endif

		std::vector<detail::RequestedValidationLayer> requestedValidationLayers;

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
			.pApplicationName = "orhi (OpenRHI)",
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
				detail::DebugMessengerUtil::GenerateCreateInfo()
			);

			createInfo.pNext = debugUtilsMessengerCreateInfo.get();
		}

		VkResult result = vkCreateInstance(
			&createInfo,
			nullptr,
			&m_handle.ReinterpretAs<VkInstance&>()
		);

		ORHI_ASSERT(result == VK_SUCCESS, "failed to create instance!");

		ORHI_LOG_INFO("Vulkan instance created successfully!");

		// If the debug utils extension is being used, setup the debug messenger
		if (useDebugUtilsExtension)
		{
			g_debugMessenger = std::make_unique<detail::DebugMessenger>(m_handle.As<VkInstance>(), *debugUtilsMessengerCreateInfo);
		}

#if defined(ORHI_USE_WINDOW_SYSTEM_WIN32)
		ORHI_ASSERT(std::get_if<data::WindowsWindow>(&p_desc.window), "incomplete Win32 window desc");

		data::WindowsWindow window = std::get<data::WindowsWindow>(p_desc.window);

		VkWin32SurfaceCreateInfoKHR surfaceCreateInfo{
			.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR,
			.hwnd = static_cast<HWND>(window.hwnd)
		};

		result = vkCreateWin32SurfaceKHR(
			m_handle.As<VkInstance>(),
			&surfaceCreateInfo,
			nullptr,
			&m_context.surface
		);

		ORHI_ASSERT(result == VK_SUCCESS, "failed to create Win32 surface");
#elif defined(ORHI_USE_WINDOW_SYSTEM_XLIB)
		ORHI_ASSERT(std::get_if<data::X11Window>(&p_desc.window), "incomplete X11 window desc");

		data::X11Window window = std::get<data::X11Window>(p_desc.window);

		VkXlibSurfaceCreateInfoKHR surfaceCreateInfo{
			.sType = VK_STRUCTURE_TYPE_XLIB_SURFACE_CREATE_INFO_KHR,
			.dpy = static_cast<::Display*>(window.dpy),
			.window = static_cast<::Window>(window.window)
		};

		result = vkCreateXlibSurfaceKHR(
			m_handle.As<VkInstance>(),
			&surfaceCreateInfo,
			nullptr,
			&m_context.surface
		);

		ORHI_ASSERT(result == VK_SUCCESS, "failed to create X11 surface");
#elif defined(ORHI_USE_WINDOW_SYSTEM_XCB)
		ORHI_ASSERT(std::get_if<data::X11Window>(&p_desc.window), "incomplete X11 window desc");

		data::X11Window window = std::get<data::X11Window>(p_desc.window);

		const auto xcbConnection = XGetXCBConnection(static_cast<::Display*>(window.dpy));
		ORHI_ASSERT(xcbConnection, "Failed to get XCB connection from X11 display");

		VkXcbSurfaceCreateInfoKHR surfaceCreateInfo{
			.sType = VK_STRUCTURE_TYPE_XCB_SURFACE_CREATE_INFO_KHR,
			.connection = xcbConnection,
			.window = static_cast<xcb_window_t>(window.window)
		};

		result = vkCreateXcbSurfaceKHR(
			m_handle.As<VkInstance>(),
			&surfaceCreateInfo,
			nullptr,
			&m_context.surface
		);

		ORHI_ASSERT(result == VK_SUCCESS, "failed to create XCB surface");
#elif defined(ORHI_USE_WINDOW_SYSTEM_WAYLAND)
		ORHI_ASSERT(std::get_if<data::WaylandWindow>(&p_desc.window), "incomplete Wayland window desc");

		data::WaylandWindow window = std::get<data::WaylandWindow>(p_desc.window);

		VkWaylandSurfaceCreateInfoKHR surfaceCreateInfo{
			.sType = VK_STRUCTURE_TYPE_WAYLAND_SURFACE_CREATE_INFO_KHR,
			.display = static_cast<wl_display*>(window.display),
			.surface = static_cast<wl_surface*>(window.surface)
		};

		result = vkCreateWaylandSurfaceKHR(
			m_handle.As<VkInstance>(),
			&surfaceCreateInfo,
			nullptr,
			&m_context.surface
		);

		ORHI_ASSERT(result == VK_SUCCESS, "failed to create Wayland surface");
#elif defined(ORHI_USE_WINDOW_SYSTEM_COCOA)
		ORHI_ASSERT(std::get_if<data::MetalWindow>(&p_desc.window), "incomplete Metal window desc");

		data::MetalWindow window = std::get<data::MetalWindow>(p_desc.window);

		VkMetalSurfaceCreateInfoEXT surfaceCreateInfo{
			.sType = VK_STRUCTURE_TYPE_METAL_SURFACE_CREATE_INFO_EXT,
			.pNext = nullptr,
			.pLayer = static_cast<CAMetalLayer*>(window.caMetalLayer)
		};

		result = vkCreateMetalSurfaceEXT(
			m_handle.As<VkInstance>(),
			&surfaceCreateInfo,
			nullptr,
			&m_context.surface
		);

		ORHI_ASSERT(result == VK_SUCCESS, "failed to create Metal surface");
#else
#error Other platforms than Win32, X11, XCB, Wayland, and Metal are not supported yet
#endif

		uint32_t deviceCount = 0;
		vkEnumeratePhysicalDevices(m_handle.As<VkInstance>(), &deviceCount, nullptr);

		ORHI_ASSERT(deviceCount > 0, "failed to find GPUs with Vulkan support!");

		std::vector<VkPhysicalDevice> physicalDevices(deviceCount);
		vkEnumeratePhysicalDevices(m_handle.As<VkInstance>(), &deviceCount, physicalDevices.data());

		for (VkPhysicalDevice physicalDevice : physicalDevices)
		{
			VkPhysicalDeviceProperties deviceProperties;
			vkGetPhysicalDeviceProperties(physicalDevice, &deviceProperties);

			VkPhysicalDeviceFeatures deviceFeatures;
			vkGetPhysicalDeviceFeatures(physicalDevice, &deviceFeatures);

			auto& device = g_physicalDevices.emplace_back(PhysicalDevice{
				.physicalDevice = physicalDevice,
				.properties = deviceProperties,
				.features = deviceFeatures,
				.extensionManager = {},
				.queueFamilyIndices = detail::QueueFamilyIndices::Create(physicalDevice, m_context.surface),
				.info = GenerateDeviceInfo(
					physicalDevice,
					deviceProperties,
					deviceFeatures,
					m_context.surface
				),
				.swapChainSupportDetails = {}
			});

			device.extensionManager.FetchExtensions<detail::EExtensionHandler::PhysicalDevice>(device.physicalDevice);
		}

		g_suitableDeviceInfos.reserve(g_physicalDevices.size());

		g_deviceRequestedExtensions.emplace_back(
			VK_KHR_SWAPCHAIN_EXTENSION_NAME, true
		);

		for (PhysicalDevice& device : g_physicalDevices)
		{
			if (IsDeviceSuitable(device, m_context.surface))
			{
				ORHI_LOG_INFO("Suitable device found: " + std::string(device.properties.deviceName));
				g_suitableDeviceInfos.emplace_back(device.info);
			}
			else
			{
				ORHI_LOG_INFO("Device not suitable: " + std::string(device.properties.deviceName));
			}
		}
	}

	template<>
	Instance::~TInstance()
	{
		g_debugMessenger.reset();
		g_createdDevices.clear();
		vkDestroySurfaceKHR(m_handle.As<VkInstance>(), m_context.surface, nullptr);
		vkDestroyInstance(m_handle.As<VkInstance>(), nullptr);
	}

	template<>
	const std::vector<data::DeviceInfo>& Instance::GetSuitableDevices() const
	{
		return g_suitableDeviceInfos;
	}

	template<>
	Device& Instance::CreateDevice(uint32_t p_deviceId)
	{
		PhysicalDevice selectedDevice = [p_deviceId]() {
			for (const PhysicalDevice& device : g_physicalDevices)
			{
				if (device.info.id == p_deviceId)
				{
					return device;
				}
			}

			ORHI_ASSERT(false, "Provided device id doesn't correspond to any valid device");
			return g_physicalDevices[0];
		}();

		std::vector<const char*> extensions = selectedDevice.extensionManager.FilterExtensions(g_deviceRequestedExtensions);

		const auto deviceCreationInfo = detail::DeviceCreationInfo{
			.physicalDevice = selectedDevice.physicalDevice,
			.properties = selectedDevice.properties,
			.features = selectedDevice.features,
			.queueFamilyIndices = selectedDevice.queueFamilyIndices,
			.swapChainSupportDetails = selectedDevice.swapChainSupportDetails,
			.extensions = extensions
		};

		return g_createdDevices.emplace_back(
			selectedDevice.info,
			&deviceCreationInfo
		);
	}

	template<>
	impl::common::NativeHandle Instance::GetSurfaceHandle() const
	{
		return m_context.surface;
	}
}

template class orhi::api::TInstance<orhi::impl::vk::BackendTraits>;

#endif // #if defined(ORHI_COMPILE_VULKAN)
