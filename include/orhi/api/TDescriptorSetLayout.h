/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/types/EGraphicsBackend.h>
#include <orhi/api/TDevice.h>
#include <orhi/data/DescriptorBinding.h>

namespace orhi::api
{
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
