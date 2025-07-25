/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry, Jian Bang Xu
* @licence: MIT
*/

#pragma once

#if defined(ORHI_COMPILE_DX12)

#include <orhi/types/EBlendFactor.h>  
#include <orhi/types/EBlendOp.h>  
#include <orhi/types/EBufferUsageFlags.h>  
#include <orhi/types/EColorComponentFlags.h>  
#include <orhi/types/EColorSpace.h>  
#include <orhi/types/ECommandBufferLevel.h>  
#include <orhi/types/ECommandBufferUsageFlags.h>  
#include <orhi/types/ECompareOp.h>  
#include <orhi/types/ECullModeFlags.h>  
#include <orhi/types/EDescriptorPoolCreateFlags.h>  
#include <orhi/types/EDescriptorType.h>  
#include <orhi/types/EDynamicState.h>  
#include <orhi/types/EFilter.h>  
#include <orhi/types/EFormat.h>  
#include <orhi/types/EFrontFace.h>  
#include <orhi/types/EIndexType.h>  
#include <orhi/types/ELogicOp.h>  
#include <orhi/types/EMemoryPropertyFlags.h>  
#include <orhi/types/EPipelineBindPoint.h>  
#include <orhi/types/EPipelineStageFlags.h>  
#include <orhi/types/EPolygonMode.h>  
#include <orhi/types/EPresentMode.h>  
#include <orhi/types/EPrimitiveTopology.h>  
#include <orhi/types/ESampleCountFlags.h>  
#include <orhi/types/ESamplerAddressMode.h>  
#include <orhi/types/ESamplerMipmapMode.h>  
#include <orhi/types/EShaderStageFlags.h>  
#include <orhi/types/EStencilOp.h>  
#include <orhi/types/ESurfaceTransformFlags.h>  
#include <orhi/types/ETextureAspectFlags.h>  
#include <orhi/types/ETextureLayout.h>  
#include <orhi/types/ETextureTiling.h>  
#include <orhi/types/ETextureType.h>  
#include <orhi/types/ETextureUsageType.h>  
#include <orhi/utils/EnumMapper.h>

#include <d3d12.h>
#include <dxgi1_6.h>

template <>
struct orhi::utils::MappingFor<orhi::types::EBufferUsageFlags, D3D12_RESOURCE_FLAGS>
{
	using EnumType = orhi::types::EBufferUsageFlags;
	using type = std::tuple<
		EnumValuePair<EnumType::NONE, D3D12_RESOURCE_FLAG_NONE>,
		EnumValuePair<EnumType::TRANSFER_SRC_BIT, D3D12_RESOURCE_FLAG_NONE>,
		EnumValuePair<EnumType::TRANSFER_DST_BIT, D3D12_RESOURCE_FLAG_NONE>,
		EnumValuePair<EnumType::UNIFORM_TEXEL_BUFFER_BIT, D3D12_RESOURCE_FLAG_NONE>,
		EnumValuePair<EnumType::STORAGE_TEXEL_BUFFER_BIT, D3D12_RESOURCE_FLAG_ALLOW_UNORDERED_ACCESS>,
		EnumValuePair<EnumType::UNIFORM_BUFFER_BIT, D3D12_RESOURCE_FLAG_NONE>,
		EnumValuePair<EnumType::STORAGE_BUFFER_BIT, D3D12_RESOURCE_FLAG_ALLOW_UNORDERED_ACCESS>,
		EnumValuePair<EnumType::INDEX_BUFFER_BIT, D3D12_RESOURCE_FLAG_NONE>,
		EnumValuePair<EnumType::VERTEX_BUFFER_BIT, D3D12_RESOURCE_FLAG_NONE>,
		EnumValuePair<EnumType::INDIRECT_BUFFER_BIT, D3D12_RESOURCE_FLAG_NONE>,
		// EnumValuePair<EnumType::SHADER_DEVICE_ADDRESS_BIT, D3D12_RESOURCE_FLAG_NONE>, // No direct equivalent in DX12
		EnumValuePair<EnumType::VIDEO_DECODE_SRC_BIT_KHR, D3D12_RESOURCE_FLAG_VIDEO_DECODE_REFERENCE_ONLY>,
		EnumValuePair<EnumType::VIDEO_DECODE_DST_BIT_KHR, D3D12_RESOURCE_FLAG_NONE>,
		EnumValuePair<EnumType::ACCELERATION_STRUCTURE_BUILD_INPUT_READ_ONLY_BIT_KHR, D3D12_RESOURCE_FLAG_RAYTRACING_ACCELERATION_STRUCTURE>,
		EnumValuePair<EnumType::ACCELERATION_STRUCTURE_STORAGE_BIT_KHR, D3D12_RESOURCE_FLAG_RAYTRACING_ACCELERATION_STRUCTURE>,
		EnumValuePair<EnumType::ALL, D3D12_RESOURCE_FLAG_ALLOW_UNORDERED_ACCESS | D3D12_RESOURCE_FLAG_ALLOW_RENDER_TARGET>
	>;
};

template <>
struct orhi::utils::MappingFor<orhi::types::ETextureUsageFlags, D3D12_RESOURCE_FLAGS>
{
	using EnumType = orhi::types::ETextureUsageFlags;
	using type = std::tuple<
		EnumValuePair<EnumType::NONE, D3D12_RESOURCE_FLAG_NONE>,
		EnumValuePair<EnumType::TRANSFER_SRC_BIT, D3D12_RESOURCE_FLAG_NONE>,
		EnumValuePair<EnumType::TRANSFER_DST_BIT, D3D12_RESOURCE_FLAG_NONE>,
		EnumValuePair<EnumType::SAMPLED_BIT, D3D12_RESOURCE_FLAG_NONE>,
		EnumValuePair<EnumType::STORAGE_BIT, D3D12_RESOURCE_FLAG_ALLOW_UNORDERED_ACCESS>,
		EnumValuePair<EnumType::COLOR_ATTACHMENT_BIT, D3D12_RESOURCE_FLAG_ALLOW_RENDER_TARGET>,
		EnumValuePair<EnumType::DEPTH_STENCIL_ATTACHMENT_BIT, D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL>,
		// EnumValuePair<EnumType::TRANSIENT_ATTACHMENT_BIT, D3D12_RESOURCE_FLAG_NONE>, // No direct equivalent in DX12
		// EnumValuePair<EnumType::INPUT_ATTACHMENT_BIT, D3D12_RESOURCE_FLAG_NONE>, // No direct equivalent in DX12
		EnumValuePair<EnumType::ALL, D3D12_RESOURCE_FLAG_ALLOW_RENDER_TARGET | D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL | D3D12_RESOURCE_FLAG_ALLOW_UNORDERED_ACCESS>
	>;
};

template <>
struct orhi::utils::MappingFor<orhi::types::EColorSpace, DXGI_COLOR_SPACE_TYPE>
{
	using EnumType = orhi::types::EColorSpace;
	using type = std::tuple<
		EnumValuePair<EnumType::SRGB_NONLINEAR_KHR, DXGI_COLOR_SPACE_RGB_FULL_G22_NONE_P709>,
		EnumValuePair<EnumType::DISPLAY_P3_NONLINEAR_EXT, DXGI_COLOR_SPACE_RGB_FULL_G22_NONE_P2020>,
		EnumValuePair<EnumType::EXTENDED_SRGB_LINEAR_EXT, DXGI_COLOR_SPACE_RGB_FULL_G10_NONE_P709>,
		EnumValuePair<EnumType::DISPLAY_P3_LINEAR_EXT, DXGI_COLOR_SPACE_RGB_FULL_G10_NONE_P709>,
		EnumValuePair<EnumType::DCI_P3_NONLINEAR_EXT, DXGI_COLOR_SPACE_RGB_FULL_G22_NONE_P2020>,
		EnumValuePair<EnumType::BT709_LINEAR_EXT, DXGI_COLOR_SPACE_RGB_FULL_G10_NONE_P709>,
		EnumValuePair<EnumType::BT709_NONLINEAR_EXT, DXGI_COLOR_SPACE_RGB_FULL_G22_NONE_P709>,
		// EnumValuePair<EnumType::BT2020_LINEAR_EXT, ???>, // No direct linear BT2020 equivalent in DXGI
		EnumValuePair<EnumType::HDR10_ST2084_EXT, DXGI_COLOR_SPACE_RGB_FULL_G2084_NONE_P2020>,
		EnumValuePair<EnumType::HDR10_HLG_EXT, DXGI_COLOR_SPACE_RGB_FULL_G22_NONE_P2020>,
		EnumValuePair<EnumType::ADOBERGB_LINEAR_EXT, DXGI_COLOR_SPACE_RGB_FULL_G10_NONE_P709>,
		EnumValuePair<EnumType::ADOBERGB_NONLINEAR_EXT, DXGI_COLOR_SPACE_RGB_FULL_G22_NONE_P709>,
		EnumValuePair<EnumType::PASS_THROUGH_EXT, DXGI_COLOR_SPACE_RGB_FULL_G22_NONE_P709>
	>;
};

// DX12 doesn't have command buffer levels like Vulkan - all command lists are primary
// template <>
// struct orhi::utils::MappingFor<orhi::types::ECommandBufferLevel, ???>
// {
//     // No DirectX 12 equivalent - DX12 only has command lists (similar to primary command buffers)
// };

// DX12 doesn't have command buffer usage flags like Vulkan
// template <>
// struct orhi::utils::MappingFor<orhi::types::ECommandBufferUsageFlags, ???>
// {
//     // No DirectX 12 equivalent - command lists don't have usage flags
// };

template <>
struct orhi::utils::MappingFor<orhi::types::EDescriptorType, D3D12_DESCRIPTOR_HEAP_TYPE>
{
	using EnumType = orhi::types::EDescriptorType;
	using type = std::tuple<
		EnumValuePair<EnumType::SAMPLER, D3D12_DESCRIPTOR_HEAP_TYPE_SAMPLER>,
		EnumValuePair<EnumType::COMBINED_IMAGE_SAMPLER, D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV>,
		EnumValuePair<EnumType::SAMPLED_IMAGE, D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV>,
		EnumValuePair<EnumType::STORAGE_IMAGE, D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV>,
		EnumValuePair<EnumType::UNIFORM_TEXEL_BUFFER, D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV>,
		EnumValuePair<EnumType::STORAGE_TEXEL_BUFFER, D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV>,
		EnumValuePair<EnumType::UNIFORM_BUFFER, D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV>,
		EnumValuePair<EnumType::STORAGE_BUFFER, D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV>,
		EnumValuePair<EnumType::UNIFORM_BUFFER_DYNAMIC, D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV>,
		EnumValuePair<EnumType::STORAGE_BUFFER_DYNAMIC, D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV>,
		EnumValuePair<EnumType::INPUT_ATTACHMENT, D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV>,
		EnumValuePair<EnumType::ACCELERATION_STRUCTURE_KHR, D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV>
	>;
};

template <>
struct orhi::utils::MappingFor<orhi::types::EFormat, DXGI_FORMAT>
{
	using EnumType = orhi::types::EFormat;
	using type = std::tuple<
		EnumValuePair<EnumType::UNDEFINED, DXGI_FORMAT_UNKNOWN>,
		// EnumValuePair<EnumType::R4G4_UNORM_PACK8, DXGI_FORMAT_UNKNOWN>, // No direct equivalent
		EnumValuePair<EnumType::R4G4B4A4_UNORM_PACK16, DXGI_FORMAT_B4G4R4A4_UNORM>,
		EnumValuePair<EnumType::B4G4R4A4_UNORM_PACK16, DXGI_FORMAT_B4G4R4A4_UNORM>,
		EnumValuePair<EnumType::R5G6B5_UNORM_PACK16, DXGI_FORMAT_B5G6R5_UNORM>,
		EnumValuePair<EnumType::B5G6R5_UNORM_PACK16, DXGI_FORMAT_B5G6R5_UNORM>,
		EnumValuePair<EnumType::R5G5B5A1_UNORM_PACK16, DXGI_FORMAT_B5G5R5A1_UNORM>,
		EnumValuePair<EnumType::B5G5R5A1_UNORM_PACK16, DXGI_FORMAT_B5G5R5A1_UNORM>,
		EnumValuePair<EnumType::A1R5G5B5_UNORM_PACK16, DXGI_FORMAT_B5G5R5A1_UNORM>,
		EnumValuePair<EnumType::R8_UNORM, DXGI_FORMAT_R8_UNORM>,
		EnumValuePair<EnumType::R8_SNORM, DXGI_FORMAT_R8_SNORM>,
		EnumValuePair<EnumType::R8_UINT, DXGI_FORMAT_R8_UINT>,
		EnumValuePair<EnumType::R8_SINT, DXGI_FORMAT_R8_SINT>,
		EnumValuePair<EnumType::R8G8_UNORM, DXGI_FORMAT_R8G8_UNORM>,
		EnumValuePair<EnumType::R8G8_SNORM, DXGI_FORMAT_R8G8_SNORM>,
		EnumValuePair<EnumType::R8G8_UINT, DXGI_FORMAT_R8G8_UINT>,
		EnumValuePair<EnumType::R8G8_SINT, DXGI_FORMAT_R8G8_SINT>,
		EnumValuePair<EnumType::R8G8B8A8_UNORM, DXGI_FORMAT_R8G8B8A8_UNORM>,
		EnumValuePair<EnumType::R8G8B8A8_SNORM, DXGI_FORMAT_R8G8B8A8_SNORM>,
		EnumValuePair<EnumType::R8G8B8A8_UINT, DXGI_FORMAT_R8G8B8A8_UINT>,
		EnumValuePair<EnumType::R8G8B8A8_SINT, DXGI_FORMAT_R8G8B8A8_SINT>,
		EnumValuePair<EnumType::R8G8B8A8_SRGB, DXGI_FORMAT_R8G8B8A8_UNORM_SRGB>,
		EnumValuePair<EnumType::B8G8R8A8_UNORM, DXGI_FORMAT_B8G8R8A8_UNORM>,
		EnumValuePair<EnumType::B8G8R8A8_SRGB, DXGI_FORMAT_B8G8R8A8_UNORM_SRGB>,
		EnumValuePair<EnumType::R16_UNORM, DXGI_FORMAT_R16_UNORM>,
		EnumValuePair<EnumType::R16_SNORM, DXGI_FORMAT_R16_SNORM>,
		EnumValuePair<EnumType::R16_UINT, DXGI_FORMAT_R16_UINT>,
		EnumValuePair<EnumType::R16_SINT, DXGI_FORMAT_R16_SINT>,
		EnumValuePair<EnumType::R16_SFLOAT, DXGI_FORMAT_R16_FLOAT>,
		EnumValuePair<EnumType::R16G16_UNORM, DXGI_FORMAT_R16G16_UNORM>,
		EnumValuePair<EnumType::R16G16_SNORM, DXGI_FORMAT_R16G16_SNORM>,
		EnumValuePair<EnumType::R16G16_UINT, DXGI_FORMAT_R16G16_UINT>,
		EnumValuePair<EnumType::R16G16_SINT, DXGI_FORMAT_R16G16_SINT>,
		EnumValuePair<EnumType::R16G16_SFLOAT, DXGI_FORMAT_R16G16_FLOAT>,
		EnumValuePair<EnumType::R16G16B16A16_UNORM, DXGI_FORMAT_R16G16B16A16_UNORM>,
		EnumValuePair<EnumType::R16G16B16A16_SNORM, DXGI_FORMAT_R16G16B16A16_SNORM>,
		EnumValuePair<EnumType::R16G16B16A16_UINT, DXGI_FORMAT_R16G16B16A16_UINT>,
		EnumValuePair<EnumType::R16G16B16A16_SINT, DXGI_FORMAT_R16G16B16A16_SINT>,
		EnumValuePair<EnumType::R16G16B16A16_SFLOAT, DXGI_FORMAT_R16G16B16A16_FLOAT>,
		EnumValuePair<EnumType::R32_UINT, DXGI_FORMAT_R32_UINT>,
		EnumValuePair<EnumType::R32_SINT, DXGI_FORMAT_R32_SINT>,
		EnumValuePair<EnumType::R32_SFLOAT, DXGI_FORMAT_R32_FLOAT>,
		EnumValuePair<EnumType::R32G32_UINT, DXGI_FORMAT_R32G32_UINT>,
		EnumValuePair<EnumType::R32G32_SINT, DXGI_FORMAT_R32G32_SINT>,
		EnumValuePair<EnumType::R32G32_SFLOAT, DXGI_FORMAT_R32G32_FLOAT>,
		EnumValuePair<EnumType::R32G32B32_UINT, DXGI_FORMAT_R32G32B32_UINT>,
		EnumValuePair<EnumType::R32G32B32_SINT, DXGI_FORMAT_R32G32B32_SINT>,
		EnumValuePair<EnumType::R32G32B32_SFLOAT, DXGI_FORMAT_R32G32B32_FLOAT>,
		EnumValuePair<EnumType::R32G32B32A32_UINT, DXGI_FORMAT_R32G32B32A32_UINT>,
		EnumValuePair<EnumType::R32G32B32A32_SINT, DXGI_FORMAT_R32G32B32A32_SINT>,
		EnumValuePair<EnumType::R32G32B32A32_SFLOAT, DXGI_FORMAT_R32G32B32A32_FLOAT>,
		EnumValuePair<EnumType::D16_UNORM, DXGI_FORMAT_D16_UNORM>,
		EnumValuePair<EnumType::D32_SFLOAT, DXGI_FORMAT_D32_FLOAT>,
		EnumValuePair<EnumType::D24_UNORM_S8_UINT, DXGI_FORMAT_D24_UNORM_S8_UINT>,
		EnumValuePair<EnumType::D32_SFLOAT_S8_UINT, DXGI_FORMAT_D32_FLOAT_S8X24_UINT>,
		EnumValuePair<EnumType::BC1_RGB_UNORM_BLOCK, DXGI_FORMAT_BC1_UNORM>,
		EnumValuePair<EnumType::BC1_RGB_SRGB_BLOCK, DXGI_FORMAT_BC1_UNORM_SRGB>,
		EnumValuePair<EnumType::BC1_RGBA_UNORM_BLOCK, DXGI_FORMAT_BC1_UNORM>,
		EnumValuePair<EnumType::BC1_RGBA_SRGB_BLOCK, DXGI_FORMAT_BC1_UNORM_SRGB>,
		EnumValuePair<EnumType::BC2_UNORM_BLOCK, DXGI_FORMAT_BC2_UNORM>,
		EnumValuePair<EnumType::BC2_SRGB_BLOCK, DXGI_FORMAT_BC2_UNORM_SRGB>,
		EnumValuePair<EnumType::BC3_UNORM_BLOCK, DXGI_FORMAT_BC3_UNORM>,
		EnumValuePair<EnumType::BC3_SRGB_BLOCK, DXGI_FORMAT_BC3_UNORM_SRGB>,
		EnumValuePair<EnumType::BC4_UNORM_BLOCK, DXGI_FORMAT_BC4_UNORM>,
		EnumValuePair<EnumType::BC4_SNORM_BLOCK, DXGI_FORMAT_BC4_SNORM>,
		EnumValuePair<EnumType::BC5_UNORM_BLOCK, DXGI_FORMAT_BC5_UNORM>,
		EnumValuePair<EnumType::BC5_SNORM_BLOCK, DXGI_FORMAT_BC5_SNORM>,
		EnumValuePair<EnumType::BC6H_UFLOAT_BLOCK, DXGI_FORMAT_BC6H_UF16>,
		EnumValuePair<EnumType::BC6H_SFLOAT_BLOCK, DXGI_FORMAT_BC6H_SF16>,
		EnumValuePair<EnumType::BC7_UNORM_BLOCK, DXGI_FORMAT_BC7_UNORM>,
		EnumValuePair<EnumType::BC7_SRGB_BLOCK, DXGI_FORMAT_BC7_UNORM_SRGB>
	>;
};

template <>
struct orhi::utils::MappingFor<orhi::types::EIndexType, DXGI_FORMAT>
{
	using EnumType = orhi::types::EIndexType;
	using type = std::tuple<
		EnumValuePair<EnumType::UINT16, DXGI_FORMAT_R16_UINT>,
		EnumValuePair<EnumType::UINT32, DXGI_FORMAT_R32_UINT>,
		EnumValuePair<EnumType::UINT8, DXGI_FORMAT_R8_UINT>
	>;
};

template <>
struct orhi::utils::MappingFor<orhi::types::EMemoryPropertyFlags, D3D12_HEAP_TYPE>
{
	using EnumType = orhi::types::EMemoryPropertyFlags;
	using type = std::tuple<
		EnumValuePair<EnumType::NONE, D3D12_HEAP_TYPE_DEFAULT>,
		EnumValuePair<EnumType::DEVICE_LOCAL_BIT, D3D12_HEAP_TYPE_DEFAULT>,
		EnumValuePair<EnumType::HOST_VISIBLE_BIT, D3D12_HEAP_TYPE_UPLOAD>,
		EnumValuePair<EnumType::HOST_COHERENT_BIT, D3D12_HEAP_TYPE_UPLOAD>,
		EnumValuePair<EnumType::HOST_CACHED_BIT, D3D12_HEAP_TYPE_READBACK>,
		// EnumValuePair<EnumType::LAZILY_ALLOCATED_BIT, ???>, // No direct equivalent in DX12
		// EnumValuePair<EnumType::PROTECTED_BIT, ???>, // No direct equivalent in DX12
		EnumValuePair<EnumType::ALL, D3D12_HEAP_TYPE_DEFAULT>
	>;
};

// DX12 doesn't have explicit pipeline bind points like Vulkan
// All pipelines are set on command lists directly
// template <>
// struct orhi::utils::MappingFor<orhi::types::EPipelineBindPoint, ???>
// {
//     // No DirectX 12 equivalent - pipelines are set directly on command lists
// };

// DX12 doesn't have present modes like Vulkan - handled by DXGI swap chain
// template <>
// struct orhi::utils::MappingFor<orhi::types::EPresentMode, ???>
// {
//     // No DirectX 12 equivalent - present mode is handled by DXGI swap chain creation
// };

// DX12 doesn't have explicit shader stage flags - stages are implicit in pipeline creation
// template <>
// struct orhi::utils::MappingFor<orhi::types::EShaderStageFlags, ???>
// {
//     // No DirectX 12 equivalent - shader stages are implicit in PSO creation
// };

// DX12 doesn't have explicit pipeline stage flags like Vulkan
// template <>
// struct orhi::utils::MappingFor<orhi::types::EPipelineStageFlags, ???>
// {
//     // No DirectX 12 equivalent - pipeline stages are handled automatically
// };

// DX12 doesn't have surface transform flags - handled by DXGI
// template <>
// struct orhi::utils::MappingFor<orhi::types::ESurfaceTransformFlags, ???>
// {
//     // No DirectX 12 equivalent - surface transforms handled by DXGI
// };

template <>
struct orhi::utils::MappingFor<orhi::types::EPrimitiveTopology, D3D_PRIMITIVE_TOPOLOGY>
{
	using EnumType = orhi::types::EPrimitiveTopology;
	using type = std::tuple<
		EnumValuePair<EnumType::POINT_LIST, D3D_PRIMITIVE_TOPOLOGY_POINTLIST>,
		EnumValuePair<EnumType::LINE_LIST, D3D_PRIMITIVE_TOPOLOGY_LINELIST>,
		EnumValuePair<EnumType::LINE_STRIP, D3D_PRIMITIVE_TOPOLOGY_LINESTRIP>,
		EnumValuePair<EnumType::TRIANGLE_LIST, D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST>,
		EnumValuePair<EnumType::TRIANGLE_STRIP, D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP>,
		EnumValuePair<EnumType::TRIANGLE_FAN, D3D_PRIMITIVE_TOPOLOGY_TRIANGLEFAN>,
		EnumValuePair<EnumType::LINE_LIST_WITH_ADJACENCY, D3D_PRIMITIVE_TOPOLOGY_LINELIST_ADJ>,
		EnumValuePair<EnumType::LINE_STRIP_WITH_ADJACENCY, D3D_PRIMITIVE_TOPOLOGY_LINESTRIP_ADJ>,
		EnumValuePair<EnumType::TRIANGLE_LIST_WITH_ADJACENCY, D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST_ADJ>,
		EnumValuePair<EnumType::TRIANGLE_STRIP_WITH_ADJACENCY, D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP_ADJ>,
		EnumValuePair<EnumType::PATCH_LIST, D3D_PRIMITIVE_TOPOLOGY_1_CONTROL_POINT_PATCHLIST> // Note: DX12 has multiple patch list types
	>;
};

template <>
struct orhi::utils::MappingFor<orhi::types::EPolygonMode, D3D12_FILL_MODE>
{
	using EnumType = orhi::types::EPolygonMode;
	using type = std::tuple<
		EnumValuePair<EnumType::FILL, D3D12_FILL_MODE_SOLID>,
		EnumValuePair<EnumType::LINE, D3D12_FILL_MODE_WIREFRAME>
		// EnumValuePair<EnumType::POINT, ???> // DX12 doesn't have point fill mode
	>;
};

template <>
struct orhi::utils::MappingFor<orhi::types::ECullModeFlags, D3D12_CULL_MODE>
{
	using EnumType = orhi::types::ECullModeFlags;
	using type = std::tuple<
		EnumValuePair<EnumType::NONE, D3D12_CULL_MODE_NONE>,
		EnumValuePair<EnumType::FRONT_BIT, D3D12_CULL_MODE_FRONT>,
		EnumValuePair<EnumType::BACK_BIT, D3D12_CULL_MODE_BACK>
		// EnumValuePair<EnumType::FRONT_AND_BACK, ???> // DX12 doesn't allow culling both front and back
	>;
};

template <>
struct orhi::utils::MappingFor<orhi::types::EFrontFace, bool>
{
	using EnumType = orhi::types::EFrontFace;
	using type = std::tuple<
		EnumValuePair<EnumType::COUNTER_CLOCKWISE, false>, // DX12 uses bool for FrontCounterClockwise
		EnumValuePair<EnumType::CLOCKWISE, true>
	>;
};

template <>
struct orhi::utils::MappingFor<orhi::types::ESampleCountFlags, UINT>
{
	using EnumType = orhi::types::ESampleCountFlags;
	using type = std::tuple<
		EnumValuePair<EnumType::COUNT_1_BIT, 1>,
		EnumValuePair<EnumType::COUNT_2_BIT, 2>,
		EnumValuePair<EnumType::COUNT_4_BIT, 4>,
		EnumValuePair<EnumType::COUNT_8_BIT, 8>,
		EnumValuePair<EnumType::COUNT_16_BIT, 16>,
		EnumValuePair<EnumType::COUNT_32_BIT, 32>,
		EnumValuePair<EnumType::COUNT_64_BIT, 64>
	>;
};

template <>
struct orhi::utils::MappingFor<orhi::types::EBlendFactor, D3D12_BLEND>
{
	using EnumType = orhi::types::EBlendFactor;
	using type = std::tuple<
		EnumValuePair<EnumType::ZERO, D3D12_BLEND_ZERO>,
		EnumValuePair<EnumType::ONE, D3D12_BLEND_ONE>,
		EnumValuePair<EnumType::SRC_COLOR, D3D12_BLEND_SRC_COLOR>,
		EnumValuePair<EnumType::ONE_MINUS_SRC_COLOR, D3D12_BLEND_INV_SRC_COLOR>,
		EnumValuePair<EnumType::DST_COLOR, D3D12_BLEND_DEST_COLOR>,
		EnumValuePair<EnumType::ONE_MINUS_DST_COLOR, D3D12_BLEND_INV_DEST_COLOR>,
		EnumValuePair<EnumType::SRC_ALPHA, D3D12_BLEND_SRC_ALPHA>,
		EnumValuePair<EnumType::ONE_MINUS_SRC_ALPHA, D3D12_BLEND_INV_SRC_ALPHA>,
		EnumValuePair<EnumType::DST_ALPHA, D3D12_BLEND_DEST_ALPHA>,
		EnumValuePair<EnumType::ONE_MINUS_DST_ALPHA, D3D12_BLEND_INV_DEST_ALPHA>,
		EnumValuePair<EnumType::CONSTANT_COLOR, D3D12_BLEND_BLEND_FACTOR>,
		EnumValuePair<EnumType::ONE_MINUS_CONSTANT_COLOR, D3D12_BLEND_INV_BLEND_FACTOR>,
		EnumValuePair<EnumType::CONSTANT_ALPHA, D3D12_BLEND_BLEND_FACTOR>,
		EnumValuePair<EnumType::ONE_MINUS_CONSTANT_ALPHA, D3D12_BLEND_INV_BLEND_FACTOR>,
		EnumValuePair<EnumType::SRC_ALPHA_SATURATE, D3D12_BLEND_SRC_ALPHA_SAT>,
		EnumValuePair<EnumType::SRC1_COLOR, D3D12_BLEND_SRC1_COLOR>,
		EnumValuePair<EnumType::ONE_MINUS_SRC1_COLOR, D3D12_BLEND_INV_SRC1_COLOR>,
		EnumValuePair<EnumType::SRC1_ALPHA, D3D12_BLEND_SRC1_ALPHA>,
		EnumValuePair<EnumType::ONE_MINUS_SRC1_ALPHA, D3D12_BLEND_INV_SRC1_ALPHA>
	>;
};

template <>
struct orhi::utils::MappingFor<orhi::types::EBlendOp, D3D12_BLEND_OP>
{
	using EnumType = orhi::types::EBlendOp;
	using type = std::tuple<
		EnumValuePair<EnumType::ADD, D3D12_BLEND_OP_ADD>,
		EnumValuePair<EnumType::SUBTRACT, D3D12_BLEND_OP_SUBTRACT>,
		EnumValuePair<EnumType::REVERSE_SUBTRACT, D3D12_BLEND_OP_REV_SUBTRACT>,
		EnumValuePair<EnumType::MIN, D3D12_BLEND_OP_MIN>,
		EnumValuePair<EnumType::MAX, D3D12_BLEND_OP_MAX>
		// The following extended blend operations are not supported in DX12:
		// EnumValuePair<EnumType::ZERO_EXT, ???>,
		// EnumValuePair<EnumType::SRC_EXT, ???>,
		// EnumValuePair<EnumType::DST_EXT, ???>,
		// ... (many more EXT blend operations not supported)
	>;
};

template <>
struct orhi::utils::MappingFor<orhi::types::EColorComponentFlags, UINT8>
{
	using EnumType = orhi::types::EColorComponentFlags;
	using type = std::tuple<
		EnumValuePair<EnumType::NONE, 0>,
		EnumValuePair<EnumType::R_BIT, D3D12_COLOR_WRITE_ENABLE_RED>,
		EnumValuePair<EnumType::G_BIT, D3D12_COLOR_WRITE_ENABLE_GREEN>,
		EnumValuePair<EnumType::B_BIT, D3D12_COLOR_WRITE_ENABLE_BLUE>,
		EnumValuePair<EnumType::A_BIT, D3D12_COLOR_WRITE_ENABLE_ALPHA>,
		EnumValuePair<EnumType::ALL, D3D12_COLOR_WRITE_ENABLE_ALL>
	>;
};

template <>
struct orhi::utils::MappingFor<orhi::types::ELogicOp, D3D12_LOGIC_OP>
{
	using EnumType = orhi::types::ELogicOp;
	using type = std::tuple<
		EnumValuePair<EnumType::CLEAR, D3D12_LOGIC_OP_CLEAR>,
		EnumValuePair<EnumType::AND, D3D12_LOGIC_OP_AND>,
		EnumValuePair<EnumType::AND_REVERSE, D3D12_LOGIC_OP_AND_REVERSE>,
		EnumValuePair<EnumType::COPY, D3D12_LOGIC_OP_COPY>,
		EnumValuePair<EnumType::AND_INVERTED, D3D12_LOGIC_OP_AND_INVERTED>,
		EnumValuePair<EnumType::NO_OP, D3D12_LOGIC_OP_NOOP>,
		EnumValuePair<EnumType::XOR, D3D12_LOGIC_OP_XOR>,
		EnumValuePair<EnumType::OR, D3D12_LOGIC_OP_OR>,
		EnumValuePair<EnumType::NOR, D3D12_LOGIC_OP_NOR>,
		EnumValuePair<EnumType::EQUIVALENT, D3D12_LOGIC_OP_EQUIV>,
		EnumValuePair<EnumType::INVERT, D3D12_LOGIC_OP_INVERT>,
		EnumValuePair<EnumType::OR_REVERSE, D3D12_LOGIC_OP_OR_REVERSE>,
		EnumValuePair<EnumType::COPY_INVERTED, D3D12_LOGIC_OP_COPY_INVERTED>,
		EnumValuePair<EnumType::OR_INVERTED, D3D12_LOGIC_OP_OR_INVERTED>,
		EnumValuePair<EnumType::NAND, D3D12_LOGIC_OP_NAND>,
		EnumValuePair<EnumType::SET, D3D12_LOGIC_OP_SET>
	>;
};

template <>
struct orhi::utils::MappingFor<orhi::types::ECompareOp, D3D12_COMPARISON_FUNC>
{
	using EnumType = orhi::types::ECompareOp;
	using type = std::tuple<
		EnumValuePair<EnumType::NEVER, D3D12_COMPARISON_FUNC_NEVER>,
		EnumValuePair<EnumType::LESS, D3D12_COMPARISON_FUNC_LESS>,
		EnumValuePair<EnumType::EQUAL, D3D12_COMPARISON_FUNC_EQUAL>,
		EnumValuePair<EnumType::LESS_OR_EQUAL, D3D12_COMPARISON_FUNC_LESS_EQUAL>,
		EnumValuePair<EnumType::GREATER, D3D12_COMPARISON_FUNC_GREATER>,
		EnumValuePair<EnumType::NOT_EQUAL, D3D12_COMPARISON_FUNC_NOT_EQUAL>,
		EnumValuePair<EnumType::GREATER_OR_EQUAL, D3D12_COMPARISON_FUNC_GREATER_EQUAL>,
		EnumValuePair<EnumType::ALWAYS, D3D12_COMPARISON_FUNC_ALWAYS>
	>;
};

template <>
struct orhi::utils::MappingFor<orhi::types::EStencilOp, D3D12_STENCIL_OP>
{
	using EnumType = orhi::types::EStencilOp;
	using type = std::tuple<
		EnumValuePair<EnumType::KEEP, D3D12_STENCIL_OP_KEEP>,
		EnumValuePair<EnumType::ZERO, D3D12_STENCIL_OP_ZERO>,
		EnumValuePair<EnumType::REPLACE, D3D12_STENCIL_OP_REPLACE>,
		EnumValuePair<EnumType::INCREMENT_AND_CLAMP, D3D12_STENCIL_OP_INCR_SAT>,
		EnumValuePair<EnumType::DECREMENT_AND_CLAMP, D3D12_STENCIL_OP_DECR_SAT>,
		EnumValuePair<EnumType::INVERT, D3D12_STENCIL_OP_INVERT>,
		EnumValuePair<EnumType::INCREMENT_AND_WRAP, D3D12_STENCIL_OP_INCR>,
		EnumValuePair<EnumType::DECREMENT_AND_WRAP, D3D12_STENCIL_OP_DECR>
	>;
};

// DirectX 12 doesn't have dynamic state like Vulkan - most state is set during PSO creation
template <>
struct orhi::utils::MappingFor<orhi::types::EDynamicState, UINT>
{
	using EnumType = orhi::types::EDynamicState;
	using type = std::tuple<
		EnumValuePair<EnumType::VIEWPORT, 0>, // Always dynamic in DX12
		EnumValuePair<EnumType::SCISSOR, 1>, // Always dynamic in DX12
		EnumValuePair<EnumType::BLEND_CONSTANTS, 2>, // Can be set per command list
		EnumValuePair<EnumType::STENCIL_REFERENCE, 3> // Can be set per command list
		// Many other dynamic states from Vulkan don't exist in DX12
	>;
};

// DX12 doesn't have descriptor pool create flags like Vulkan
// template <>
// struct orhi::utils::MappingFor<orhi::types::EDescriptorPoolCreateFlags, ???>
// {
//     // No DirectX 12 equivalent - descriptor heaps are simpler
// };

template <>
struct orhi::utils::MappingFor<orhi::types::ETextureType, D3D12_RESOURCE_DIMENSION>
{
	using EnumType = orhi::types::ETextureType;
	using type = std::tuple<
		EnumValuePair<EnumType::TEXTURE_1D, D3D12_RESOURCE_DIMENSION_TEXTURE1D>,
		EnumValuePair<EnumType::TEXTURE_2D, D3D12_RESOURCE_DIMENSION_TEXTURE2D>,
		EnumValuePair<EnumType::TEXTURE_3D, D3D12_RESOURCE_DIMENSION_TEXTURE3D>
	>;
};

// DX12 doesn't have texture tiling like Vulkan - all textures are optimally tiled by default
// template <>
// struct orhi::utils::MappingFor<orhi::types::ETextureTiling, ???>
// {
//     // No DirectX 12 equivalent - all textures are optimally tiled
// };

// DX12 doesn't have explicit texture layouts like Vulkan - handled by resource states
// template <>
// struct orhi::utils::MappingFor<orhi::types::ETextureLayout, ???>
// {
//     // No DirectX 12 equivalent - uses resource states instead
// };

template <>
struct orhi::utils::MappingFor<orhi::types::ESamplerAddressMode, D3D12_TEXTURE_ADDRESS_MODE>
{
	using EnumType = orhi::types::ESamplerAddressMode;
	using type = std::tuple<
		EnumValuePair<EnumType::REPEAT, D3D12_TEXTURE_ADDRESS_MODE_WRAP>,
		EnumValuePair<EnumType::MIRRORED_REPEAT, D3D12_TEXTURE_ADDRESS_MODE_MIRROR>,
		EnumValuePair<EnumType::CLAMP_TO_EDGE, D3D12_TEXTURE_ADDRESS_MODE_CLAMP>,
		EnumValuePair<EnumType::CLAMP_TO_BORDER, D3D12_TEXTURE_ADDRESS_MODE_BORDER>,
		EnumValuePair<EnumType::MIRROR_CLAMP_TO_EDGE, D3D12_TEXTURE_ADDRESS_MODE_MIRROR_ONCE>
	>;
};

// template <>
// struct orhi::utils::MappingFor<orhi::types::EFilter, D3D12_FILTER_TYPE>
// {
// 	using EnumType = orhi::types::EFilter;
// 	using type = std::tuple<
// 		EnumValuePair<EnumType::NEAREST, D3D12_FILTER_TYPE_POINT>,
// 		EnumValuePair<EnumType::LINEAR, D3D12_FILTER_TYPE_LINEAR>
// 	>;
// };
// template <> 
// struct orhi::utils::MappingFor<orhi::types::ESamplerMipmapMode, D3D12_FILTER>
// {
//     // No DirectX 12 equivalent - mipmap filtering is part of D3D12_FILTER
// };

/*
	DX12 doesn't have separate mipmap modes - it's part of the filter
	Instead we use GetDX12Filter function to get the appropriate filter based on min/mag/mipmap modes
	All possible return values from GetDX12Filter:
	
	Standard Filtering (anisotropic=false, compareEnabled=false):
	- NEAREST, NEAREST, NEAREST  -> D3D12_FILTER_MIN_MAG_MIP_POINT (0x0)
	- LINEAR,  NEAREST, NEAREST  -> D3D12_FILTER_MIN_LINEAR_MAG_MIP_POINT (0x10)
	- NEAREST, LINEAR,  NEAREST  -> D3D12_FILTER_MIN_POINT_MAG_LINEAR_MIP_POINT (0x4)
	- LINEAR,  LINEAR,  NEAREST  -> D3D12_FILTER_MIN_MAG_LINEAR_MIP_POINT (0x14)
	- NEAREST, NEAREST, LINEAR   -> D3D12_FILTER_MIN_MAG_POINT_MIP_LINEAR (0x1)
	- LINEAR,  NEAREST, LINEAR   -> D3D12_FILTER_MIN_LINEAR_MAG_POINT_MIP_LINEAR (0x11)
	- NEAREST, LINEAR,  LINEAR   -> D3D12_FILTER_MIN_POINT_MAG_MIP_LINEAR (0x5)
	- LINEAR,  LINEAR,  LINEAR   -> D3D12_FILTER_MIN_MAG_MIP_LINEAR (0x15)
	
	Comparison Filtering (anisotropic=false, compareEnabled=true):
	- NEAREST, NEAREST, NEAREST  -> D3D12_FILTER_COMPARISON_MIN_MAG_MIP_POINT (0x80)
	- LINEAR,  NEAREST, NEAREST  -> D3D12_FILTER_COMPARISON_MIN_LINEAR_MAG_MIP_POINT (0x90)
	- NEAREST, LINEAR,  NEAREST  -> D3D12_FILTER_COMPARISON_MIN_POINT_MAG_LINEAR_MIP_POINT (0x84)
	- LINEAR,  LINEAR,  NEAREST  -> D3D12_FILTER_COMPARISON_MIN_MAG_LINEAR_MIP_POINT (0x94)
	- NEAREST, NEAREST, LINEAR   -> D3D12_FILTER_COMPARISON_MIN_MAG_POINT_MIP_LINEAR (0x81)
	- LINEAR,  NEAREST, LINEAR   -> D3D12_FILTER_COMPARISON_MIN_LINEAR_MAG_POINT_MIP_LINEAR (0x91)
	- NEAREST, LINEAR,  LINEAR   -> D3D12_FILTER_COMPARISON_MIN_POINT_MAG_MIP_LINEAR (0x85)
	- LINEAR,  LINEAR,  LINEAR   -> D3D12_FILTER_COMPARISON_MIN_MAG_MIP_LINEAR (0x95)
	
	Anisotropic Filtering (anisotropic=true, compareEnabled=false):
	- (any), (any), NEAREST      -> D3D12_FILTER_MIN_MAG_ANISOTROPIC_MIP_POINT (0x54)
	- (any), (any), LINEAR       -> D3D12_FILTER_ANISOTROPIC (0x55)
	
	Comparison Anisotropic Filtering (anisotropic=true, compareEnabled=true):
	- (any), (any), NEAREST      -> D3D12_FILTER_COMPARISON_MIN_MAG_ANISOTROPIC_MIP_POINT (0xd4)
	- (any), (any), LINEAR       -> D3D12_FILTER_COMPARISON_ANISOTROPIC (0xd5)

	TODO:
	* Add unit tests for GetDX12Filter to ensure all combinations return expected values
	* Right now VkSamplerReductionMode is not supported, so we don't handle it here, but we can add it later if needed.
*/
constexpr D3D12_FILTER GetDX12Filter(
	orhi::types::EFilter minFilter,
	orhi::types::EFilter magFilter,
	orhi::types::EFilter mipmapMode,
	bool anisotropic,
	bool compareEnabled
)
{
	// Handle anisotropic filtering first
	if (anisotropic)
	{
		if (compareEnabled)
		{
			// Comparison anisotropic filtering
			return mipmapMode == orhi::types::EFilter::NEAREST ? 
				D3D12_FILTER_COMPARISON_MIN_MAG_ANISOTROPIC_MIP_POINT : 
				D3D12_FILTER_COMPARISON_ANISOTROPIC;
		}
		else
		{
			// Standard anisotropic filtering
			return mipmapMode == orhi::types::EFilter::NEAREST ? 
				D3D12_FILTER_MIN_MAG_ANISOTROPIC_MIP_POINT : 
				D3D12_FILTER_ANISOTROPIC;
		}
	}

	uint32_t filterValue = 
		static_cast<uint32_t>(mipmapMode) |			// Mip filter: bits 0-1
		(static_cast<uint32_t>(magFilter) << 2) |	// Mag filter: bits 2-3
		(static_cast<uint32_t>(minFilter) << 4) |	// Min filter: bits 4-5
		(compareEnabled ? 0x80 : 0);				// Comparison bit: bit 7 (if enabled)

	return static_cast<D3D12_FILTER>(filterValue);
}

// DX12 doesn't have texture aspect flags like Vulkan
// template <>
// struct orhi::utils::MappingFor<orhi::types::ETextureAspectFlags, ???>
// {
//     // No DirectX 12 equivalent - aspects are handled implicitly
// };

#endif // #if defined(ORHI_COMPILE_DX12)
