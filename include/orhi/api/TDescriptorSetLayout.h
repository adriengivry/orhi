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
	template<types::EGraphicsBackend Backend, CTX_SIG_DCL>
	class TDescriptorSetLayout final
	{
	public:
		/**
		* Creates a shader module
		* @param p_device
		*/
		TDescriptorSetLayout(
			TDevice<Backend, CTX_SIG_FWD>& p_device,
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
		DescriptorSetLayoutContext m_context;
	};
}
