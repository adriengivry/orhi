/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <vector>
#include <filesystem>
#include <span>
#include <orhi/data/NativeHandle.h>
#include <vulkan/vulkan.h>

namespace orhi::impl::vk::details
{
	class MemoryUtils
	{
	public:
		// Input need to be a class with GetHandle() (VkObject)
		template<class Output, class Input>
		static std::vector<Output> PrepareArray(std::initializer_list<std::reference_wrapper<Input>> p_elements)
		{
			std::vector<Output> output;
			output.reserve(p_elements.size());
			for (const auto& element : p_elements)
			{
				output.push_back(element.get().GetNativeHandle().As<Output>());
			}
			return output;
		}

		// Input need to be a class with GetHandle() (VkObject)
		template<class Output, class Input>
		static std::vector<Output> PrepareArray(std::span<const std::reference_wrapper<Input>> p_elements)
		{
			std::vector<Output> output;
			output.reserve(p_elements.size());
			for (const auto& element : p_elements)
			{
				output.push_back(element.get().GetNativeHandle().As<Output>());
			}
			return output;
		}

		static uint32_t FindMemoryType(
			VkPhysicalDevice p_physicalDevice,
			uint32_t p_typeFilter,
			VkMemoryPropertyFlags p_properties
		);
	};
}
