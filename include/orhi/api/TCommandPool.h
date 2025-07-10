/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/types/EGraphicsBackend.h>
#include <orhi/api/TCommandBuffer.h>
#include <orhi/types/ECommandBufferLevel.h>

namespace orhi::api
{
	template<
		types::EGraphicsBackend Backend,
		class CommandPoolContext,
		class DeviceContext,
		class CommandBufferContext,
		class RenderPassContext,
		class FramebufferContext,
		class BufferContext,
		class DescriptorSetContext,
		class TextureContext,
		class DescriptorContext
	>
	class TCommandPool final
	{
	public:
		/**
		* Creates a command pool
		*/
		TCommandPool(
			TDevice<Backend, DeviceContext>& p_device
		);

		/**
		* Destroys the command pool
		*/
		~TCommandPool();

		/**
		* Allocates a command buffer from the command pool
		*/
		std::vector<std::reference_wrapper<TCommandBuffer<Backend, CommandBufferContext, DeviceContext, RenderPassContext, FramebufferContext, BufferContext, DescriptorSetContext, TextureContext, DescriptorContext>>> AllocateCommandBuffers(
			uint32_t p_count,
			types::ECommandBufferLevel p_level = types::ECommandBufferLevel::PRIMARY
		);

		/**
		* Returns the underlying object's native handle
		*/
		data::NativeHandle GetNativeHandle() const;

	private:
		CommandPoolContext m_context;
	};
}
