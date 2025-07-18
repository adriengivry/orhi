/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#if defined(ORHI_COMPILE_VULKAN)

#include <orhi/impl/vk/Texture.h>

#include <orhi/debug/Assert.h>
#include <orhi/debug/Log.h>
#include <orhi/impl/vk/detail/MemoryUtils.h>
#include <orhi/impl/vk/detail/Types.h>

#include <vulkan/vulkan.h>

using namespace orhi::impl::vk;

namespace orhi
{
	template<>
	Texture::TTexture(
		Device& p_device,
		const data::TextureDesc& p_desc
	) : m_context{
		.device = p_device,
		.memory = VK_NULL_HANDLE,
		.allocatedBytes = 0ULL
	}
	{
		VkImageCreateInfo createInfo{
			.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO,
			.flags = 0, // TODO: expose this setting
			.imageType = utils::EnumToValue<VkImageType>(p_desc.type),
			.format = utils::EnumToValue<VkFormat>(p_desc.format),
			.extent = reinterpret_cast<const VkExtent3D&>(p_desc.extent),
			.mipLevels = p_desc.mipLevels,
			.arrayLayers = p_desc.arrayLayers,
			.samples = static_cast<VkSampleCountFlagBits>(utils::EnumToValue<VkSampleCountFlags>(p_desc.samples)),
			.tiling = utils::EnumToValue<VkImageTiling>(p_desc.tiling),
			.usage = utils::EnumToValue<VkImageUsageFlags>(p_desc.usage),
			.sharingMode = VK_SHARING_MODE_EXCLUSIVE,
			.initialLayout = utils::EnumToValue<VkImageLayout>(p_desc.initialLayout),
		};

		VkResult result = vkCreateImage(
			m_context.device.GetNativeHandle().As<VkDevice>(),
			&createInfo,
			nullptr,
			&m_handle.ReinterpretAs<VkImage&>()
		);

		ORHI_ASSERT(result == VK_SUCCESS, "failed to create image!");

		m_context.format = p_desc.format;
		m_context.extent = p_desc.extent;
	}

	template<>
	Texture::~TTexture()
	{
		if (IsAllocated())
		{
			Deallocate();
		}

		vkDestroyImage(
			m_context.device.GetNativeHandle().As<VkDevice>(),
			m_handle.As<VkImage>(),
			nullptr
		);
	}

	template<>
	bool Texture::IsAllocated() const
	{
		return
			m_context.memory != VK_NULL_HANDLE &&
			m_context.allocatedBytes > 0;
	}

	template<>
	void Texture::Allocate(types::EMemoryPropertyFlags p_properties)
	{
		ORHI_ASSERT(!IsAllocated(), "Texture is already allocated");

		VkMemoryRequirements memRequirements;
		vkGetImageMemoryRequirements(
			m_context.device.GetNativeHandle().As<VkDevice>(),
			m_handle.As<VkImage>(),
			&memRequirements
		);

		const auto memoryType = detail::MemoryUtils::FindMemoryType(
			m_context.device.GetAdapterNativeHandle().As<VkPhysicalDevice>(),
			memRequirements.memoryTypeBits,
			utils::EnumToValue<VkMemoryPropertyFlags>(p_properties)
		);

		VkMemoryAllocateInfo allocInfo{
			.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
			.allocationSize = memRequirements.size,
			.memoryTypeIndex = memoryType
		};

		VkResult result = vkAllocateMemory(
			m_context.device.GetNativeHandle().As<VkDevice>(),
			&allocInfo,
			nullptr,
			&m_context.memory
		);

		ORHI_ASSERT(result == VK_SUCCESS, "failed to allocate texture memory!");

		vkBindImageMemory(
			m_context.device.GetNativeHandle().As<VkDevice>(),
			m_handle.As<VkImage>(),
			m_context.memory,
			0
		);

		m_context.allocatedBytes = memRequirements.size;
	}

	template<>
	void Texture::Deallocate()
	{
		ORHI_ASSERT(IsAllocated(), "Cannot deallocate a texture that isn't allocated");

		vkFreeMemory(
			m_context.device.GetNativeHandle().As<VkDevice>(),
			m_context.memory,
			nullptr
		);

		m_context.memory = VK_NULL_HANDLE;
	}

	template<>
	void Texture::Upload(
		const void* p_data,
		std::optional<data::MemoryRange> p_memoryRange
	)
	{
		ORHI_ASSERT(IsAllocated(), "Uploading to unnallocated image");

		ORHI_ASSERT(
			!p_memoryRange.has_value() || p_memoryRange->offset + p_memoryRange->size <= m_context.allocatedBytes,
			"Uploading out of allocated image bounds"
		);

		const uint64_t offset = p_memoryRange.has_value() ? p_memoryRange->offset : 0;
		const uint64_t size = p_memoryRange.has_value() ? p_memoryRange->size : m_context.allocatedBytes;

		void* destPtr;
		VkResult result = vkMapMemory(
			m_context.device.GetNativeHandle().As<VkDevice>(),
			m_context.memory,
			offset,
			size,
			0,
			&destPtr
		);

		ORHI_ASSERT(result == VK_SUCCESS, "failed to map texture memory!");

		std::memcpy(destPtr, p_data, size);

		vkUnmapMemory(
			m_context.device.GetNativeHandle().As<VkDevice>(),
			m_context.memory
		);
	}

	template<>
	uint64_t Texture::GetAllocatedBytes() const
	{
		return m_context.allocatedBytes;
	}

	template<>
	types::EFormat Texture::GetFormat() const
	{
		return m_context.format;
	}

	template<>
	const math::Extent3D& Texture::GetExtent() const
	{
		return m_context.extent;
	}

	template<>
	uint32_t Texture::GetMipLevels() const
	{
		return m_context.mipLevels;
	}
}

template class orhi::api::TTexture<orhi::impl::vk::BackendTraits>;

#endif // #if defined(ORHI_COMPILE_VULKAN)
