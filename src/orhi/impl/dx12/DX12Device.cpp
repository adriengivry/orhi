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
		const data::DeviceInfo& p_deviceInfo,
		const void* p_deviceCreationInfo
	) : m_context{
		
		}
	{
		
	}

	template<>
	Device::~TDevice()
	{
		
	}

	// For DX12, we have separate graphics and compute queues, we might need to break this API into two methods
	Queue& Device::GetGraphicsAndComputeQueue() const
	{
		return *m_context.directQueue;
	}

	// For DX12, we don't have a separate present queue, the graphics queue is used for presentation
	Queue& Device::GetPresentQueue() const
	{
		return *m_context.directQueue;
	}

	template<>
	data::SwapChainDesc Device::GetOptimalSwapChainDesc(const math::Extent2D& p_windowSize)
	{
		return data::SwapChainDesc{

		};
	}

	template<>
	data::QueuesDesc Device::GetQueuesDesc() const
	{
		return data::QueuesDesc {
		};
	}

	template<>
	void Device::WaitIdle() const
	{
	}

	template<>
	const data::DeviceInfo& Device::GetInfo() const
	{
		return m_context.deviceInfo;
	}

	template<>
	impl::common::NativeHandle Device::GetAdapterNativeHandle() const
	{
		return m_context.physicalDevice.Get();
	}
}

template class orhi::api::TDevice<orhi::impl::dx12::BackendTraits>;

#endif // #if defined(ORHI_COMPILE_DX12)
