/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry, Jian Bang Xu
* @licence: MIT
*/

#pragma once

#include <orhi/api/TDevice.h>
#include <orhi/data/DeviceInfo.h>
#include <orhi/impl/dx12/BackendTraits.h>
#include <orhi/impl/dx12/Queue.h>

#include <memory>
#include <vector>

#include <orhi/impl/dx12/detail/ComPtr.h>

struct ID3D12Device;

namespace orhi::impl::dx12
{
	struct DeviceContext
	{
		Microsoft::WRL::ComPtr<ID3D12Device> physicalDevice = nullptr;
		data::DeviceInfo deviceInfo;
		std::unique_ptr<Queue> directQueue;
		std::unique_ptr<Queue> computeQueue;
		std::unique_ptr<Queue> copyQueue;
	};

	using Device = api::TDevice<BackendTraits>;
}
