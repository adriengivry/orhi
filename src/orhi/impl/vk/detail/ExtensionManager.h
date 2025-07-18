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
	struct RequestedExtension
	{
		std::string name;
		bool required;
	};

	enum class EExtensionHandler
	{
		Instance,
		PhysicalDevice
	};

	class ExtensionManager
	{
	public:
		/**
		* Creates the extension manager
		*/
		ExtensionManager() = default;

		/**
		* Destroys the extension manager
		*/
		virtual ~ExtensionManager() = default;

		/**
		* Fetch extensions for the given handler
		*/
		template<EExtensionHandler HandlerType>
		void FetchExtensions(void* p_handler = nullptr);

		/**
		* Returns true if a given extension is supported
		*/
		bool IsExtensionSupported(const std::string_view extension) const;

		/**
		* Prints the given list of extensions to the console
		*/
		void LogExtensions() const;

		/**
		* Returns a formatted list of available extensions, skipping any unsupported extension,
		* and returning an error if a required extension isn't available
		*/
		std::vector<const char*> FilterExtensions(std::span<const RequestedExtension> p_requestedExtensions) const;

	private:
		std::vector<VkExtensionProperties> m_extensions;
	};
}

#endif // #if defined(ORHI_COMPILE_VULKAN)
