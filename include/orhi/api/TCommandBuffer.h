/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/types/EGraphicsBackend.h>
#include <orhi/data/NativeHandle.h>
#include <orhi/types/ECommandBufferUsageFlags.h>
#include <orhi/types/EPipelineBindPoint.h>
#include <orhi/types/EIndexType.h>
#include <orhi/types/ETextureLayout.h>
#include <orhi/api/TFramebuffer.h>
#include <orhi/api/TRenderPass.h>
#include <orhi/api/TBuffer.h>
#include <orhi/api/TTexture.h>
#include <orhi/api/TDescriptorSet.h>
#include <orhi/api/TGraphicsPipeline.h>
#include <orhi/data/Rect2D.h>
#include <orhi/data/ViewportDesc.h>
#include <orhi/data/BufferCopyDesc.h>
#include <orhi/data/BufferTextureCopyDesc.h>
#include <orhi/api/TContextRegistry.h>

namespace orhi::api
{
	template<types::EGraphicsBackend Backend, typename ContextRegistry>
	class TCommandBuffer final
	{
	public:
		/**
		* Creates a command buffer
		*/
		TCommandBuffer(data::NativeHandle p_handle);

		/**
		* Destroys the command buffer
		*/
		~TCommandBuffer();

		/**
		* Resets the command buffer
		*/
		void Reset();

		/**
		* Begin recording commands
		*/
		void Begin(types::ECommandBufferUsageFlags p_flags = types::ECommandBufferUsageFlags::NONE);

		/**
		* Finish recording commands
		*/
		void End();

		/**
		* Begin a render pass
		*/
		void BeginRenderPass(
			TRenderPass<Backend, ContextRegistry>& p_renderPass,
			TFramebuffer<Backend, ContextRegistry>& p_framebuffer,
			std::pair<uint32_t, uint32_t> p_extent
		);

		/**
		* End a render pass
		*/
		void EndRenderPass();

		/**
		* Copy buffer content from source to destination
		*/
		void CopyBuffer(
			TBuffer<Backend, ContextRegistry>& p_src,
			TBuffer<Backend, ContextRegistry>& p_dest,
			std::span<const data::BufferCopyDesc> p_regions = {}
		);

		/**
		* Copy buffer content from source buffer to destination texture
		*/
		void CopyBufferToTexture(
			TBuffer<Backend, ContextRegistry>& p_src,
			TTexture<Backend, ContextRegistry>& p_dest,
			std::span<const data::BufferTextureCopyDesc> p_regions = {}
		);

		/**
		* Transition a texture from one layout to another
		*/
		void TransitionTextureLayout(
			TTexture<Backend, ContextRegistry>& p_texture,
			types::ETextureLayout p_layout
		);

		/**
		* Bind a graphics pipeline
		*/
		void BindPipeline(
			types::EPipelineBindPoint p_bindPoint,
			data::NativeHandle p_pipeline
		);

		/**
		* Bind index buffer
		*/
		void BindIndexBuffer(
			const TBuffer<Backend, ContextRegistry>& p_indexBuffer,
			uint64_t p_offset = 0,
			types::EIndexType p_indexType = types::EIndexType::UINT32
		);

		/**
		* Bind vertex buffers
		*/
		void BindVertexBuffers(
			std::span<const std::reference_wrapper<TBuffer<Backend, ContextRegistry>>> p_buffers,
			std::span<const uint64_t> p_offsets
		);

		/**
		* Bind descriptor sets
		*/
		void BindDescriptorSets(
			std::span<const std::reference_wrapper<TDescriptorSet<Backend, ContextRegistry>>> p_descriptorSets,
			data::NativeHandle p_pipelineLayout
		);

		/**
		* Set viewport
		*/
		void SetViewport(const data::ViewportDesc& p_viewport);

		/**
		* Set scissor
		*/
		void SetScissor(const data::Rect2D& p_scissor);

		/**
		* Submit a draw command
		*/
		void Draw(uint32_t p_vertexCount, uint32_t p_instanceCount = 1);

		/**
		* Submit an indexed draw command
		*/
		void DrawIndexed(uint32_t p_indexCount, uint32_t p_instanceCount = 1);

		/**
		* Returns the underlying object's native handle
		*/
		data::NativeHandle GetNativeHandle() const;

	private:
		typename ContextRegistry::CommandBufferContext m_context;
	};
}
