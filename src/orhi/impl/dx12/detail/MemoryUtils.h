/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry, Jian Bang Xu
* @licence: MIT
*/

#pragma once

#if defined(ORHI_COMPILE_DX12)

#include <orhi/impl/common/NativeHandle.h>

#include <d3d12.h>
#include <dxgi1_4.h>

#include <filesystem>
#include <span>
#include <vector>

namespace orhi::impl::dx12::detail
{
	class MemoryUtils
	{
	public:
		// Input need to be a class with GetHandle() (D3D12Object)
		template<class Output, class Input>
		static std::vector<Output> PrepareArray(std::initializer_list<std::reference_wrapper<Input>> p_elements)
		{
			std::vector<Output> output;
			output.reserve(p_elements.size());
			for (const auto& element : p_elements)
			{
				output.push_back(element.get().GetNativeHandle().As<Output>());
			}
			return output;
		}

		// Input need to be a class with GetHandle() (D3D12Object)
		template<class Output, class Input>
		static std::vector<Output> PrepareArray(std::span<const std::reference_wrapper<Input>> p_elements)
		{
			std::vector<Output> output;
			output.reserve(p_elements.size());
			for (const auto& element : p_elements)
			{
				output.push_back(element.get().GetNativeHandle().As<Output>());
			}
			return output;
		}

		static D3D12_HEAP_TYPE GetBestHeapType(D3D12_RESOURCE_STATES p_initialState);
	};
}

#endif // #if defined(ORHI_COMPILE_DX12)
