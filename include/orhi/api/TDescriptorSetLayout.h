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
	template<typename ContextRegistry>
	class TDescriptorSetLayout final
	{
	public:
		/**
		* Creates a shader module
		* @param p_device
		*/
		TDescriptorSetLayout(
			TDevice<ContextRegistry>& p_device,
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
		ContextRegistry::DescriptorSetLayoutContext m_context;
	};
}
