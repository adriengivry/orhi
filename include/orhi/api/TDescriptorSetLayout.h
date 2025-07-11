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

	template<typename BackendTraits>
	class TDescriptorSetLayout final
	{
	public:
		/**
		* Creates a shader module
		* @param p_device
		*/
		TDescriptorSetLayout(
			TDevice<BackendTraits>& p_device,
			std::initializer_list<data::DescriptorBinding> p_bindings
		);

		/**
		* Destroys the shader module
		*/
		~TDescriptorSetLayout();

		/**
		* Returns the underlying object's native handle
		*/
		data::NativeHandle GetNativeHandle() const;

	private:
		BackendTraits::DescriptorSetLayoutContext m_context;
	};
}
