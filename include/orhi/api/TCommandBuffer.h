/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/data/BufferCopyDesc.h>
#include <orhi/data/BufferTextureCopyDesc.h>
#include <orhi/data/ClearValue.h>
#include <orhi/data/MemoryRange.h>
#include <orhi/data/TextureRegion.h>
#include <orhi/data/ViewportDesc.h>
#include <orhi/impl/common/BackendObject.h>
#include <orhi/math/Rect2D.h>
#include <orhi/types/ECommandBufferUsageFlags.h>
#include <orhi/types/EGraphicsBackend.h>
#include <orhi/types/EIndexType.h>
#include <orhi/types/EPipelineBindPoint.h>
#include <orhi/types/EShaderStageFlags.h>
#include <orhi/types/ETextureLayout.h>

#include <initializer_list>
#include <span>

namespace orhi::api
{
	template<typename BackendTraits> class TBuffer;
	template<typename BackendTraits> class TDescriptorSet;
	template<typename BackendTraits> class TFramebuffer;
	template<typename BackendTraits> class TPipeline;
	template<typename BackendTraits> class TPipelineLayout;
	template<typename BackendTraits> class TRenderPass;
	template<typename BackendTraits> class TTexture;

	/**
	* @brief A command buffer for recording and submitting GPU commands
	* 
	* TCommandBuffer provides a cross-platform abstraction for recording graphics and compute commands
	* that will be executed on the GPU. Commands are recorded between Begin() and End() calls, and
	* can include render passes, resource bindings, draw calls, and memory operations.
	* 
	* @tparam BackendTraits Backend-specific traits defining implementation types
	*/
	template<typename BackendTraits>
	class TCommandBuffer final : public impl::common::BackendObject
	{
	public:
		/**
		* @brief Creates a command buffer from a native handle
		* @param p_handle Native handle to the underlying command buffer object
		*/
		TCommandBuffer(impl::common::NativeHandle p_handle);

		/**
		* @brief Destroys the command buffer and releases associated resources
		*/
		~TCommandBuffer();

		/**
		* @brief Resets the command buffer to its initial state
		* @note All previously recorded commands are discarded
		*/
		void Reset();

		/**
		* @brief Begins recording commands to the command buffer
		* @param p_flags Usage flags controlling how the command buffer will be used
		*/
		void Begin(types::ECommandBufferUsageFlags p_flags = types::ECommandBufferUsageFlags::NONE);

		/**
		* @brief Finishes recording commands to the command buffer
		* @note After calling End(), no more commands can be recorded until Reset() and Begin() are called again
		*/
		void End();

		/**
		* @brief Begins a render pass for rendering operations
		* @param p_renderPass The render pass to begin
		* @param p_framebuffer The framebuffer to render to
		* @param p_extent The rendering extent as a pair of width and height
		* @param p_clearValues Optional array of clear values for attachments; if empty, no clearing is performed
		*/
		void BeginRenderPass(
			TRenderPass<BackendTraits>& p_renderPass,
			TFramebuffer<BackendTraits>& p_framebuffer,
			math::Extent2D p_extent,
			std::initializer_list<data::ClearValue> p_clearValues = {}
		);

		/**
		* @brief Ends the current render pass
		* @note Must be called after BeginRenderPass() and all rendering commands
		*/
		void EndRenderPass();

		/**
		* @brief Copies data between two buffers
		* @param p_src Source buffer to copy from
		* @param p_dest Destination buffer to copy to
		* @param p_regions Array of copy regions specifying source offset, destination offset, and size; if empty, copies entire buffer
		*/
		void CopyBuffer(
			TBuffer<BackendTraits>& p_src,
			TBuffer<BackendTraits>& p_dest,
			std::span<const data::BufferCopyDesc> p_regions = {}
		);

		/**
		* @brief Copies data from a buffer to a texture
		* @param p_src Source buffer containing the image data
		* @param p_dest Destination texture to copy to
		* @param p_layout (optional) Texture layout to transition to after copy, defaults to TRANSFER_DST_OPTIMAL
		* @param p_regions Array of copy regions specifying buffer offset, texture subresource, and extent; if empty, copies entire buffer to texture
		*/
		void CopyBufferToTexture(
			TBuffer<BackendTraits>& p_src,
			TTexture<BackendTraits>& p_dest,
			types::ETextureLayout p_layout = types::ETextureLayout::TRANSFER_DST_OPTIMAL,
			std::span<const data::BufferTextureCopyDesc> p_regions = {}
		);

		/**
		* @brief Transitions a texture from one layout to another
		* @param p_texture The texture to transition
		* @param p_oldLayout The current layout of the texture
		* @param p_newLayout The new layout to transition the texture to
		* @param p_mipLevel (optional) Base mip level to transition, defaults to 0 
		* @param p_mipLevelCount (optional) Number of mip levels to transition, defaults to 1
		*/
		void TransitionTextureLayout(
			TTexture<BackendTraits>& p_texture,
			types::ETextureLayout p_oldLayout,
			types::ETextureLayout p_newLayout,
			uint32_t p_baseMipLevel = 0,
			uint32_t p_mipLevelCount = 1
		);

		/**
		* @brief Blits a texture from one region to another, potentially resizing it
		* @param p_src Source texture to blit from
		* @param p_dest Destination texture to blit to
		* @param p_srcRegion Source region to blit from
		* @param p_destRegion Destination region to blit to
		* @param p_srcLayout (optional) Source texture layout, defaults to TRANSFER_SRC_OPTIMAL
		* @param p_destLayout (optional) Destination texture layout, defaults to TRANSFER_DST_OPTIMAL
		*/
		void BlitTexture(
			TTexture<BackendTraits>& p_src,
			TTexture<BackendTraits>& p_dest,
			const data::TextureRegion& p_srcRegion,
			const data::TextureRegion& p_destRegion,
			types::ETextureLayout p_srcLayout = types::ETextureLayout::TRANSFER_SRC_OPTIMAL,
			types::ETextureLayout p_destLayout = types::ETextureLayout::TRANSFER_DST_OPTIMAL
		);

		/**
		* @brief Binds a pipeline for subsequent operations
		* @param p_bindPoint The pipeline bind point (graphics or compute)
		* @param p_pipeline The pipeline to bind
		*/
		void BindPipeline(
			types::EPipelineBindPoint p_bindPoint,
			TPipeline<BackendTraits>& p_pipeline
		);

		/**
		* @brief Binds an index buffer for indexed drawing operations
		* @param p_indexBuffer The buffer containing index data
		* @param p_offset Byte offset into the index buffer
		* @param p_indexType The data type of the indices
		*/
		void BindIndexBuffer(
			const TBuffer<BackendTraits>& p_indexBuffer,
			uint64_t p_offset = 0,
			types::EIndexType p_indexType = types::EIndexType::UINT32
		);

		/**
		* @brief Binds vertex buffers for vertex data input
		* @param p_buffers Array of vertex buffers to bind
		* @param p_offsets Array of byte offsets into each vertex buffer
		*/
		void BindVertexBuffers(
			std::span<const std::reference_wrapper<TBuffer<BackendTraits>>> p_buffers,
			std::span<const uint64_t> p_offsets
		);

		/**
		* @brief Binds descriptor sets containing shader resources
		* @param p_descriptorSets Array of descriptor sets to bind
		* @param p_pipelineLayout Pipeline layout defining the resource interface
		* @param p_bindPoint (optional) The pipeline bind point for which the descriptor sets are bound; defaults to GRAPHICS
		*/
		void BindDescriptorSets(
			std::span<const std::reference_wrapper<TDescriptorSet<BackendTraits>>> p_descriptorSets,
			TPipelineLayout<BackendTraits>& p_pipelineLayout,
			types::EPipelineBindPoint p_bindPoint = types::EPipelineBindPoint::GRAPHICS
		);

		/**
		* @brief Pushes constants to the pipeline for shader stages
		* @param p_pipelineLayout Pipeline layout defining the push constant ranges
		* @param p_stageFlags Shader stages to which the constants apply
		* @param p_range Memory range specifying the size and offset of the constants
		* @param p_data Pointer to the data to push
		*/
		void PushConstants(
			TPipelineLayout<BackendTraits>& p_pipelineLayout,
			types::EShaderStageFlags p_stageFlags,
			const data::MemoryRange& p_range,
			const void* p_data
		);

		/**
		* @brief Sets the viewport for rendering operations
		* @param p_viewport Viewport descriptor specifying position, size, and depth range
		*/
		void SetViewport(const data::ViewportDesc& p_viewport);

		/**
		* @brief Sets the scissor rectangle for rendering operations
		* @param p_scissor Rectangle descriptor specifying the scissor test area
		*/
		void SetScissor(const math::Rect2D& p_scissor);

		/**
		* @brief Submits a non-indexed draw command
		* @param p_vertexCount Number of vertices to draw
		* @param p_instanceCount Number of instances to draw
		*/
		void Draw(uint32_t p_vertexCount, uint32_t p_instanceCount = 1);

		/**
		* @brief Submits an indexed draw command
		* @param p_indexCount Number of indices to draw
		* @param p_instanceCount Number of instances to draw
		*/
		void DrawIndexed(uint32_t p_indexCount, uint32_t p_instanceCount = 1);

		/**
		* @brief Submits a compute dispatch command
		* @param p_groupCountX Number of workgroups in the X dimension
		* @param p_groupCountY Number of workgroups in the Y dimension (default is 1)
		* @param p_groupCountZ Number of workgroups in the Z dimension (default is 1)
		*/
		void Dispatch(
			uint32_t p_groupCountX,
			uint32_t p_groupCountY = 1,
			uint32_t p_groupCountZ = 1
		);

	private:
		BackendTraits::CommandBufferContext m_context;
	};
}
