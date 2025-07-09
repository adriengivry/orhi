/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#if defined(ORHI_COMPILE_VULKAN)

#include <orhi/debug/Assert.h>
#include <orhi/debug/Log.h>
#include <orhi/impl/vk/ShaderModule.h>
#include <vulkan/vulkan.h>

using namespace orhi::impl::vk;

namespace orhi
{
	template<>
	ShaderModule::TShaderModule(
		Device& p_device,
		const std::span<const std::byte> p_source
	) : m_context{
		.device = p_device,
		.handle = VK_NULL_HANDLE
	}
	{
		VkShaderModuleCreateInfo createInfo{
			.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO,
			.codeSize = p_source.size(),
			.pCode = reinterpret_cast<const uint32_t*>(p_source.data())
		};

		VkResult result = vkCreateShaderModule(
			m_context.device.GetNativeHandle().As<VkDevice>(),
			&createInfo,
			nullptr,
			&m_context.handle
		);
		
		ORHI_ASSERT(result == VK_SUCCESS, "failed to create shader module!");
	}

	template<>
	ShaderModule::~TShaderModule()
	{
		vkDestroyShaderModule(
			m_context.device.GetNativeHandle().As<VkDevice>(),
			m_context.handle,
			nullptr
		);
	}

	template<>
	data::NativeHandle ShaderModule::GetNativeHandle() const
	{
		return m_context.handle;
	}
}

#endif // #if defined(ORHI_COMPILE_VULKAN)
