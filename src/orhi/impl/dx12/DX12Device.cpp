/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry, Jian Bang Xu
* @licence: MIT
*/

#if defined(ORHI_COMPILE_DX12)

#include <orhi/impl/dx12/Device.h>

#include <orhi/debug/Assert.h>
#include <orhi/debug/Log.h>
#include <orhi/impl/dx12/detail/Types.h>

#include <d3d12.h>
#include <dxgi1_6.h>

using namespace orhi::impl::dx12;

namespace orhi
{
	template<>
	Device::TDevice(
		const data::DeviceDesc& p_desc
	)
	{
		
	}

	template<>
	Device::~TDevice()
	{
		
	}

	template<>
	const data::DeviceInfo& Device::GetDeviceInfo() const
	{
		static data::DeviceInfo info;
		return info;
	}

	template<>
	Queue& Device::GetQueue(types::EQueueType p_queueType)
	{
		static Queue* queue = nullptr;
		return *queue;
	}
}

template class orhi::api::TDevice<orhi::impl::dx12::BackendTraits>;

#endif // #if defined(ORHI_COMPILE_DX12)
