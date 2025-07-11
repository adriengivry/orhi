/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/data/DescriptorBinding.h>
#include <orhi/data/NativeHandle.h>
#include <orhi/types/EGraphicsBackend.h>

#include <initializer_list>

namespace orhi::api
{
	template<typename BackendTraits> class TDevice;

	/**
	* @brief A descriptor set layout defining the structure of descriptor sets
	* 
	* TDescriptorSetLayout defines the types, binding points, and shader stages
	* for descriptors within a descriptor set. It serves as a template for
	* creating compatible descriptor sets and pipeline layouts.
	* 
	* @tparam BackendTraits Backend-specific traits defining implementation types
	*/
	template<typename BackendTraits>
	class TDescriptorSetLayout final
	{
	public:
		/**
		* @brief Creates a descriptor set layout with the specified bindings
		* @param p_device Reference to the device that will own this descriptor set layout
		* @param p_bindings List of descriptor bindings defining the layout structure
		*/
		TDescriptorSetLayout(
			TDevice<BackendTraits>& p_device,
			std::initializer_list<data::DescriptorBinding> p_bindings
		);

		/**
		* @brief Destroys the descriptor set layout and releases associated resources
		*/
		~TDescriptorSetLayout();

		/**
		* @brief Gets the native handle for backend-specific operations
		* @return Native handle to the underlying descriptor set layout object
		*/
		data::NativeHandle GetNativeHandle() const;

	private:
		BackendTraits::DescriptorSetLayoutContext m_context;
	};
}
