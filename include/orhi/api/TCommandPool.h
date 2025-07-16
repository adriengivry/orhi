/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/detail/Object.h>
#include <orhi/types/ECommandBufferLevel.h>
#include <orhi/types/EGraphicsBackend.h>

#include <vector>

namespace orhi::api
{
	template<typename BackendTraits> class TCommandBuffer;
	template<typename BackendTraits> class TDevice;

	/**
	* @brief A command pool for allocating command buffers
	* 
	* TCommandPool manages the allocation and deallocation of command buffers.
	* Command buffers allocated from the same pool share memory and are intended
	* to be used on the same queue family.
	* 
	* @tparam BackendTraits Backend-specific traits defining implementation types
	*/
	template<typename BackendTraits>
	class TCommandPool final : public detail::Object
	{
	public:
		/**
		* @brief Creates a command pool for the specified device
		* @param p_device Reference to the device that will own this command pool
		*/
		TCommandPool(
			TDevice<BackendTraits>& p_device
		);

		/**
		* @brief Destroys the command pool and all associated command buffers
		*/
		~TCommandPool();

		/**
		* @brief Allocates command buffers from this pool
		* @param p_count Number of command buffers to allocate
		* @param p_level Command buffer level (primary or secondary)
		* @return Vector of references to the allocated command buffers
		*/
		std::vector<std::reference_wrapper<TCommandBuffer<BackendTraits>>> AllocateCommandBuffers(
			uint32_t p_count,
			types::ECommandBufferLevel p_level = types::ECommandBufferLevel::PRIMARY
		);

	private:
		BackendTraits::CommandPoolContext m_context;
	};
}
