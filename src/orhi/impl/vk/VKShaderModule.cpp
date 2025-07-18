/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#if defined(ORHI_COMPILE_VULKAN)

#include <orhi/impl/vk/ShaderModule.h>

#include <orhi/debug/Assert.h>
#include <orhi/debug/Log.h>

#include <vulkan/vulkan.h>

using namespace orhi::impl::vk;

namespace orhi
{
	template<>
	ShaderModule::TShaderModule(
		Device& p_device,
		const std::span<const std::byte> p_source
	) : m_context{
		.device = p_device
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
			&m_handle.ReinterpretAs<VkShaderModule&>()
		);
		
		ORHI_ASSERT(result == VK_SUCCESS, "failed to create shader module!");
	}

	template<>
	ShaderModule::~TShaderModule()
	{
		vkDestroyShaderModule(
			m_context.device.GetNativeHandle().As<VkDevice>(),
			m_handle.As<VkShaderModule>(),
			nullptr
		);
	}
}

template class orhi::api::TShaderModule<orhi::impl::vk::BackendTraits>;

#endif // #if defined(ORHI_COMPILE_VULKAN)
