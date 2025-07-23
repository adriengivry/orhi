/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry, Jian Bang Xu
* @licence: MIT
*/

#if defined(ORHI_COMPILE_DX12)

#include <orhi/impl/dx12/Instance.h>

#include <orhi/debug/Assert.h>
#include <orhi/debug/Log.h>
#include <orhi/impl/dx12/detail/Types.h>

#include <d3d12.h>
#include <dxgi1_6.h>

using namespace orhi::impl::dx12;

namespace orhi
{
	template<>
	Instance::TInstance(
		const data::InstanceDesc& p_desc
	)
	{
		
	}

	template<>
	Instance::~TInstance()
	{
		
	}

	template<>
	std::vector<data::DeviceInfo> Instance::EnumerateDevices() const
	{
		return {};
	}

	template<>
	std::unique_ptr<Device> Instance::CreateDevice(
		const data::DeviceDesc& p_desc
	)
	{
		return nullptr;
	}
}

template class orhi::api::TInstance<orhi::impl::dx12::BackendTraits>;

#endif // #if defined(ORHI_COMPILE_DX12)
