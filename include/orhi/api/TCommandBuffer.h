/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/data/BufferCopyDesc.h>
#include <orhi/data/BufferTextureCopyDesc.h>
#include <orhi/data/NativeHandle.h>
#include <orhi/data/Rect2D.h>
#include <orhi/data/ViewportDesc.h>
#include <orhi/types/ECommandBufferUsageFlags.h>
#include <orhi/types/EGraphicsBackend.h>
#include <orhi/types/EIndexType.h>
#include <orhi/types/EPipelineBindPoint.h>
#include <orhi/types/ETextureLayout.h>

#include <span>

namespace orhi::api
{
	template<typename BackendTraits> class TBuffer;
	template<typename BackendTraits> class TDescriptorSet;
	template<typename BackendTraits> class TFramebuffer;
	template<typename BackendTraits> class TGraphicsPipeline;
	template<typename BackendTraits> class TRenderPass;
	template<typename BackendTraits> class TTexture;

	template<typename BackendTraits>
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
			TRenderPass<BackendTraits>& p_renderPass,
			TFramebuffer<BackendTraits>& p_framebuffer,
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
			TBuffer<BackendTraits>& p_src,
			TBuffer<BackendTraits>& p_dest,
			std::span<const data::BufferCopyDesc> p_regions = {}
		);

		/**
		* Copy buffer content from source buffer to destination texture
		*/
		void CopyBufferToTexture(
			TBuffer<BackendTraits>& p_src,
			TTexture<BackendTraits>& p_dest,
			std::span<const data::BufferTextureCopyDesc> p_regions = {}
		);

		/**
		* Transition a texture from one layout to another
		*/
		void TransitionTextureLayout(
			TTexture<BackendTraits>& p_texture,
			types::ETextureLayout p_layout
		);

		/**
		* Bind a graphics pipeline
		*/
		void BindPipeline(
			types::EPipelineBindPoint p_bindPoint,
			TGraphicsPipeline<BackendTraits>& p_pipeline
		);

		/**
		* Bind index buffer
		*/
		void BindIndexBuffer(
			const TBuffer<BackendTraits>& p_indexBuffer,
			uint64_t p_offset = 0,
			types::EIndexType p_indexType = types::EIndexType::UINT32
		);

		/**
		* Bind vertex buffers
		*/
		void BindVertexBuffers(
			std::span<const std::reference_wrapper<TBuffer<BackendTraits>>> p_buffers,
			std::span<const uint64_t> p_offsets
		);

		/**
		* Bind descriptor sets
		*/
		void BindDescriptorSets(
			std::span<const std::reference_wrapper<TDescriptorSet<BackendTraits>>> p_descriptorSets,
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
		BackendTraits::CommandBufferContext m_context;
	};
}
