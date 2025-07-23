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
		EnumValuePair<EnumType::SHADER_DEVICE_ADDRESS_BIT, D3D12_RESOURCE_FLAG_NONE>,
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
		EnumValuePair<EnumType::TRANSIENT_ATTACHMENT_BIT, D3D12_RESOURCE_FLAG_NONE>,
		EnumValuePair<EnumType::INPUT_ATTACHMENT_BIT, D3D12_RESOURCE_FLAG_NONE>,
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
		EnumValuePair<EnumType::BT2020_LINEAR_EXT, DXGI_COLOR_SPACE_RGB_FULL_G10_NONE_P2020>,
		EnumValuePair<EnumType::HDR10_ST2084_EXT, DXGI_COLOR_SPACE_RGB_FULL_G2084_NONE_P2020>,
		EnumValuePair<EnumType::HDR10_HLG_EXT, DXGI_COLOR_SPACE_RGB_FULL_G22_NONE_P2020>,
		EnumValuePair<EnumType::ADOBERGB_LINEAR_EXT, DXGI_COLOR_SPACE_RGB_FULL_G10_NONE_P709>,
		EnumValuePair<EnumType::ADOBERGB_NONLINEAR_EXT, DXGI_COLOR_SPACE_RGB_FULL_G22_NONE_P709>,
		EnumValuePair<EnumType::PASS_THROUGH_EXT, DXGI_COLOR_SPACE_RGB_FULL_G22_NONE_P709>
	>;
};

template <>
struct orhi::utils::MappingFor<orhi::types::ECommandBufferLevel, VkCommandBufferLevel>
{
	using EnumType = orhi::types::ECommandBufferLevel;
	using type = std::tuple<
		EnumValuePair<EnumType::PRIMARY, VK_COMMAND_BUFFER_LEVEL_PRIMARY>,
		EnumValuePair<EnumType::SECONDARY, VK_COMMAND_BUFFER_LEVEL_SECONDARY>
	>;
};

template <>
struct orhi::utils::MappingFor<orhi::types::ECommandBufferUsageFlags, VkCommandBufferUsageFlags>
{
	using EnumType = orhi::types::ECommandBufferUsageFlags;
	using type = std::tuple<
		EnumValuePair<EnumType::NONE, 0>,
		EnumValuePair<EnumType::ONE_TIME_SUBMIT_BIT, VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT>,
		EnumValuePair<EnumType::RENDER_PASS_CONTINUE_BIT, VK_COMMAND_BUFFER_USAGE_RENDER_PASS_CONTINUE_BIT>,
		EnumValuePair<EnumType::SIMULTANEOUS_USE_BIT, VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT>,
		EnumValuePair<EnumType::ALL, VK_COMMAND_BUFFER_USAGE_FLAG_BITS_MAX_ENUM>
	>;
};

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
		EnumValuePair<EnumType::R4G4_UNORM_PACK8, DXGI_FORMAT_UNKNOWN>, // No direct equivalent
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
		EnumValuePair<EnumType::ALL, D3D12_HEAP_TYPE_DEFAULT>
	>;
};

template <>
struct orhi::utils::MappingFor<orhi::types::EPipelineBindPoint, VkPipelineBindPoint>
{
	using EnumType = orhi::types::EPipelineBindPoint;
	using type = std::tuple<
		EnumValuePair<EnumType::GRAPHICS, VK_PIPELINE_BIND_POINT_GRAPHICS>,
		EnumValuePair<EnumType::COMPUTE, VK_PIPELINE_BIND_POINT_COMPUTE>,
		EnumValuePair<EnumType::RAY_TRACING_KHR, VK_PIPELINE_BIND_POINT_RAY_TRACING_KHR>,
		EnumValuePair<EnumType::SUBPASS_SHADING_HUAWEI, VK_PIPELINE_BIND_POINT_SUBPASS_SHADING_HUAWEI>,
		EnumValuePair<EnumType::RAY_TRACING_NV, VK_PIPELINE_BIND_POINT_RAY_TRACING_NV>
	>;
};

template <>
struct orhi::utils::MappingFor<orhi::types::EPresentMode, VkPresentModeKHR>
{
	using EnumType = orhi::types::EPresentMode;
	using type = std::tuple<
		EnumValuePair<EnumType::IMMEDIATE_KHR, VK_PRESENT_MODE_IMMEDIATE_KHR>,
		EnumValuePair<EnumType::MAILBOX_KHR, VK_PRESENT_MODE_MAILBOX_KHR>,
		EnumValuePair<EnumType::FIFO_KHR, VK_PRESENT_MODE_FIFO_KHR>,
		EnumValuePair<EnumType::FIFO_RELAXED_KHR, VK_PRESENT_MODE_FIFO_RELAXED_KHR>,
		EnumValuePair<EnumType::SHARED_DEMAND_REFRESH_KHR, VK_PRESENT_MODE_SHARED_DEMAND_REFRESH_KHR>,
		EnumValuePair<EnumType::SHARED_CONTINUOUS_REFRESH_KHR, VK_PRESENT_MODE_SHARED_CONTINUOUS_REFRESH_KHR>,
		EnumValuePair<EnumType::FIFO_LATEST_READY_EXT, VK_PRESENT_MODE_FIFO_LATEST_READY_EXT>
	>;
};

template <>
struct orhi::utils::MappingFor<orhi::types::EShaderStageFlags, VkShaderStageFlags>
{
	using EnumType = orhi::types::EShaderStageFlags;
	using type = std::tuple<
		EnumValuePair<EnumType::NONE, 0>,
		EnumValuePair<EnumType::VERTEX_BIT, VK_SHADER_STAGE_VERTEX_BIT>,
		EnumValuePair<EnumType::TESSELLATION_CONTROL_BIT, VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT>,
		EnumValuePair<EnumType::TESSELLATION_EVALUATION_BIT, VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT>,
		EnumValuePair<EnumType::GEOMETRY_BIT, VK_SHADER_STAGE_GEOMETRY_BIT>,
		EnumValuePair<EnumType::FRAGMENT_BIT, VK_SHADER_STAGE_FRAGMENT_BIT>,
		EnumValuePair<EnumType::COMPUTE_BIT, VK_SHADER_STAGE_COMPUTE_BIT>,
		EnumValuePair<EnumType::ALL_GRAPHICS, VK_SHADER_STAGE_ALL_GRAPHICS>,
		EnumValuePair<EnumType::RAYGEN_BIT_KHR, VK_SHADER_STAGE_RAYGEN_BIT_KHR>,
		EnumValuePair<EnumType::ANY_HIT_BIT_KHR, VK_SHADER_STAGE_ANY_HIT_BIT_KHR>,
		EnumValuePair<EnumType::CLOSEST_HIT_BIT_KHR, VK_SHADER_STAGE_CLOSEST_HIT_BIT_KHR>,
		EnumValuePair<EnumType::MISS_BIT_KHR, VK_SHADER_STAGE_MISS_BIT_KHR>,
		EnumValuePair<EnumType::INTERSECTION_BIT_KHR, VK_SHADER_STAGE_INTERSECTION_BIT_KHR>,
		EnumValuePair<EnumType::CALLABLE_BIT_KHR, VK_SHADER_STAGE_CALLABLE_BIT_KHR>,
		EnumValuePair<EnumType::TASK_BIT_EXT, VK_SHADER_STAGE_TASK_BIT_EXT>,
		EnumValuePair<EnumType::MESH_BIT_EXT, VK_SHADER_STAGE_MESH_BIT_EXT>,
		EnumValuePair<EnumType::SUBPASS_SHADING_BIT_HUAWEI, VK_SHADER_STAGE_SUBPASS_SHADING_BIT_HUAWEI>,
		EnumValuePair<EnumType::CLUSTER_CULLING_BIT_HUAWEI, VK_SHADER_STAGE_CLUSTER_CULLING_BIT_HUAWEI>,
		EnumValuePair<EnumType::RAYGEN_BIT_NV, VK_SHADER_STAGE_RAYGEN_BIT_NV>,
		EnumValuePair<EnumType::ANY_HIT_BIT_NV, VK_SHADER_STAGE_ANY_HIT_BIT_NV>,
		EnumValuePair<EnumType::CLOSEST_HIT_BIT_NV, VK_SHADER_STAGE_CLOSEST_HIT_BIT_NV>,
		EnumValuePair<EnumType::MISS_BIT_NV, VK_SHADER_STAGE_MISS_BIT_NV>,
		EnumValuePair<EnumType::INTERSECTION_BIT_NV, VK_SHADER_STAGE_INTERSECTION_BIT_NV>,
		EnumValuePair<EnumType::CALLABLE_BIT_NV, VK_SHADER_STAGE_CALLABLE_BIT_NV>,
		EnumValuePair<EnumType::TASK_BIT_NV, VK_SHADER_STAGE_TASK_BIT_NV>,
		EnumValuePair<EnumType::MESH_BIT_NV, VK_SHADER_STAGE_MESH_BIT_NV>,
		EnumValuePair<EnumType::ALL, VK_SHADER_STAGE_ALL>
	>;
};

template <>
struct orhi::utils::MappingFor<orhi::types::EPipelineStageFlags, VkPipelineStageFlags>
{
	using EnumType = orhi::types::EPipelineStageFlags;
	using type = std::tuple<
		EnumValuePair<EnumType::NONE, 0>,
		EnumValuePair<EnumType::TOP_OF_PIPE_BIT, VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT>,
		EnumValuePair<EnumType::DRAW_INDIRECT_BIT, VK_PIPELINE_STAGE_DRAW_INDIRECT_BIT>,
		EnumValuePair<EnumType::VERTEX_INPUT_BIT, VK_PIPELINE_STAGE_VERTEX_INPUT_BIT>,
		EnumValuePair<EnumType::VERTEX_SHADER_BIT, VK_PIPELINE_STAGE_VERTEX_SHADER_BIT>,
		EnumValuePair<EnumType::TESSELLATION_CONTROL_SHADER_BIT, VK_PIPELINE_STAGE_TESSELLATION_CONTROL_SHADER_BIT>,
		EnumValuePair<EnumType::TESSELLATION_EVALUATION_SHADER_BIT, VK_PIPELINE_STAGE_TESSELLATION_EVALUATION_SHADER_BIT>,
		EnumValuePair<EnumType::GEOMETRY_SHADER_BIT, VK_PIPELINE_STAGE_GEOMETRY_SHADER_BIT>,
		EnumValuePair<EnumType::FRAGMENT_SHADER_BIT, VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT>,
		EnumValuePair<EnumType::EARLY_FRAGMENT_TESTS_BIT, VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT>,
		EnumValuePair<EnumType::LATE_FRAGMENT_TESTS_BIT, VK_PIPELINE_STAGE_LATE_FRAGMENT_TESTS_BIT>,
		EnumValuePair<EnumType::COLOR_ATTACHMENT_OUTPUT_BIT, VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT>,
		EnumValuePair<EnumType::COMPUTE_SHADER_BIT, VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT>,
		EnumValuePair<EnumType::TRANSFER_BIT, VK_PIPELINE_STAGE_TRANSFER_BIT>,
		EnumValuePair<EnumType::BOTTOM_OF_PIPE_BIT, VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT>,
		EnumValuePair<EnumType::HOST_BIT, VK_PIPELINE_STAGE_HOST_BIT>,
		EnumValuePair<EnumType::ALL_GRAPHICS_BIT, VK_PIPELINE_STAGE_ALL_GRAPHICS_BIT>,
		EnumValuePair<EnumType::ALL_COMMANDS_BIT, VK_PIPELINE_STAGE_ALL_COMMANDS_BIT>,
		EnumValuePair<EnumType::TRANSFORM_FEEDBACK_BIT_EXT, VK_PIPELINE_STAGE_TRANSFORM_FEEDBACK_BIT_EXT>,
		EnumValuePair<EnumType::CONDITIONAL_RENDERING_BIT_EXT, VK_PIPELINE_STAGE_CONDITIONAL_RENDERING_BIT_EXT>,
		EnumValuePair<EnumType::ACCELERATION_STRUCTURE_BUILD_BIT_KHR, VK_PIPELINE_STAGE_ACCELERATION_STRUCTURE_BUILD_BIT_KHR>,
		EnumValuePair<EnumType::RAY_TRACING_SHADER_BIT_KHR, VK_PIPELINE_STAGE_RAY_TRACING_SHADER_BIT_KHR>,
		EnumValuePair<EnumType::TASK_SHADER_BIT_EXT, VK_PIPELINE_STAGE_TASK_SHADER_BIT_EXT>,
		EnumValuePair<EnumType::MESH_SHADER_BIT_EXT, VK_PIPELINE_STAGE_MESH_SHADER_BIT_EXT>,
		EnumValuePair<EnumType::FRAGMENT_DENSITY_PROCESS_BIT_EXT, VK_PIPELINE_STAGE_FRAGMENT_DENSITY_PROCESS_BIT_EXT>,
		EnumValuePair<EnumType::FRAGMENT_SHADING_RATE_ATTACHMENT_BIT_KHR, VK_PIPELINE_STAGE_FRAGMENT_SHADING_RATE_ATTACHMENT_BIT_KHR>,
		EnumValuePair<EnumType::COMMAND_PREPROCESS_BIT_EXT, VK_PIPELINE_STAGE_COMMAND_PREPROCESS_BIT_EXT>,
		EnumValuePair<EnumType::SHADING_RATE_IMAGE_BIT_NV, VK_PIPELINE_STAGE_SHADING_RATE_IMAGE_BIT_NV>,
		EnumValuePair<EnumType::RAY_TRACING_SHADER_BIT_NV, VK_PIPELINE_STAGE_RAY_TRACING_SHADER_BIT_NV>,
		EnumValuePair<EnumType::ACCELERATION_STRUCTURE_BUILD_BIT_NV, VK_PIPELINE_STAGE_ACCELERATION_STRUCTURE_BUILD_BIT_NV>,
		EnumValuePair<EnumType::TASK_SHADER_BIT_NV, VK_PIPELINE_STAGE_TASK_SHADER_BIT_NV>,
		EnumValuePair<EnumType::MESH_SHADER_BIT_NV, VK_PIPELINE_STAGE_MESH_SHADER_BIT_NV>,
		EnumValuePair<EnumType::ALL, VK_PIPELINE_STAGE_FLAG_BITS_MAX_ENUM>
	>;
};

template <>
struct orhi::utils::MappingFor<orhi::types::ESurfaceTransformFlags, VkSurfaceTransformFlagsKHR>
{
	using EnumType = orhi::types::ESurfaceTransformFlags;
	using type = std::tuple<
		EnumValuePair<EnumType::NONE, 0>,
		EnumValuePair<EnumType::IDENTITY_BIT_KHR, VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR>,
		EnumValuePair<EnumType::ROTATE_90_BIT_KHR, VK_SURFACE_TRANSFORM_ROTATE_90_BIT_KHR>,
		EnumValuePair<EnumType::ROTATE_180_BIT_KHR, VK_SURFACE_TRANSFORM_ROTATE_180_BIT_KHR>,
		EnumValuePair<EnumType::ROTATE_270_BIT_KHR, VK_SURFACE_TRANSFORM_ROTATE_270_BIT_KHR>,
		EnumValuePair<EnumType::HORIZONTAL_MIRROR_BIT_KHR, VK_SURFACE_TRANSFORM_HORIZONTAL_MIRROR_BIT_KHR>,
		EnumValuePair<EnumType::HORIZONTAL_MIRROR_ROTATE_90_BIT_KHR, VK_SURFACE_TRANSFORM_HORIZONTAL_MIRROR_ROTATE_90_BIT_KHR>,
		EnumValuePair<EnumType::HORIZONTAL_MIRROR_ROTATE_180_BIT_KHR, VK_SURFACE_TRANSFORM_HORIZONTAL_MIRROR_ROTATE_180_BIT_KHR>,
		EnumValuePair<EnumType::HORIZONTAL_MIRROR_ROTATE_270_BIT_KHR, VK_SURFACE_TRANSFORM_HORIZONTAL_MIRROR_ROTATE_270_BIT_KHR>,
		EnumValuePair<EnumType::INHERIT_BIT_KHR, VK_SURFACE_TRANSFORM_INHERIT_BIT_KHR>,
		EnumValuePair<EnumType::ALL, VK_SURFACE_TRANSFORM_FLAG_BITS_MAX_ENUM_KHR>
	>;
};

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
		EnumValuePair<EnumType::PATCH_LIST, D3D_PRIMITIVE_TOPOLOGY_1_CONTROL_POINT_PATCHLIST> // We have many patch lists in the enum?
	>;
};

template <>
struct orhi::utils::MappingFor<orhi::types::EPolygonMode, D3D12_FILL_MODE>
{
	using EnumType = orhi::types::EPolygonMode;
	using type = std::tuple<
		EnumValuePair<EnumType::FILL, D3D12_FILL_MODE_SOLID>,
		EnumValuePair<EnumType::LINE, D3D12_FILL_MODE_WIREFRAME>,
		EnumValuePair<EnumType::POINT, D3D12_FILL_MODE_SOLID> // DX12 doesn't have point fill mode
	>;
};

template <>
struct orhi::utils::MappingFor<orhi::types::ECullModeFlags, D3D12_CULL_MODE>
{
	using EnumType = orhi::types::ECullModeFlags;
	using type = std::tuple<
		EnumValuePair<EnumType::NONE, D3D12_CULL_MODE_NONE>,
		EnumValuePair<EnumType::FRONT_BIT, D3D12_CULL_MODE_FRONT>,
		EnumValuePair<EnumType::BACK_BIT, D3D12_CULL_MODE_BACK>,
		EnumValuePair<EnumType::FRONT_AND_BACK, D3D12_CULL_MODE_NONE> // DX12 does not allow culling both front and back
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
		EnumValuePair<EnumType::ADD, VK_BLEND_OP_ADD>,
		EnumValuePair<EnumType::SUBTRACT, VK_BLEND_OP_SUBTRACT>,
		EnumValuePair<EnumType::REVERSE_SUBTRACT, VK_BLEND_OP_REVERSE_SUBTRACT>,
		EnumValuePair<EnumType::MIN, VK_BLEND_OP_MIN>,
		EnumValuePair<EnumType::MAX, VK_BLEND_OP_MAX>,
		EnumValuePair<EnumType::ZERO_EXT, VK_BLEND_OP_ZERO_EXT>,
		EnumValuePair<EnumType::SRC_EXT, VK_BLEND_OP_SRC_EXT>,
		EnumValuePair<EnumType::DST_EXT, VK_BLEND_OP_DST_EXT>,
		EnumValuePair<EnumType::SRC_OVER_EXT, VK_BLEND_OP_SRC_OVER_EXT>,
		EnumValuePair<EnumType::DST_OVER_EXT, VK_BLEND_OP_DST_OVER_EXT>,
		EnumValuePair<EnumType::SRC_IN_EXT, VK_BLEND_OP_SRC_IN_EXT>,
		EnumValuePair<EnumType::DST_IN_EXT, VK_BLEND_OP_DST_IN_EXT>,
		EnumValuePair<EnumType::SRC_OUT_EXT, VK_BLEND_OP_SRC_OUT_EXT>,
		EnumValuePair<EnumType::DST_OUT_EXT, VK_BLEND_OP_DST_OUT_EXT>,
		EnumValuePair<EnumType::SRC_ATOP_EXT, VK_BLEND_OP_SRC_ATOP_EXT>,
		EnumValuePair<EnumType::DST_ATOP_EXT, VK_BLEND_OP_DST_ATOP_EXT>,
		EnumValuePair<EnumType::XOR_EXT, VK_BLEND_OP_XOR_EXT>,
		EnumValuePair<EnumType::MULTIPLY_EXT, VK_BLEND_OP_MULTIPLY_EXT>,
		EnumValuePair<EnumType::SCREEN_EXT, VK_BLEND_OP_SCREEN_EXT>,
		EnumValuePair<EnumType::OVERLAY_EXT, VK_BLEND_OP_OVERLAY_EXT>,
		EnumValuePair<EnumType::DARKEN_EXT, VK_BLEND_OP_DARKEN_EXT>,
		EnumValuePair<EnumType::LIGHTEN_EXT, VK_BLEND_OP_LIGHTEN_EXT>,
		EnumValuePair<EnumType::COLORDODGE_EXT, VK_BLEND_OP_COLORDODGE_EXT>,
		EnumValuePair<EnumType::COLORBURN_EXT, VK_BLEND_OP_COLORBURN_EXT>,
		EnumValuePair<EnumType::HARDLIGHT_EXT, VK_BLEND_OP_HARDLIGHT_EXT>,
		EnumValuePair<EnumType::SOFTLIGHT_EXT, VK_BLEND_OP_SOFTLIGHT_EXT>,
		EnumValuePair<EnumType::DIFFERENCE_EXT, VK_BLEND_OP_DIFFERENCE_EXT>,
		EnumValuePair<EnumType::EXCLUSION_EXT, VK_BLEND_OP_EXCLUSION_EXT>,
		EnumValuePair<EnumType::INVERT_EXT, VK_BLEND_OP_INVERT_EXT>,
		EnumValuePair<EnumType::INVERT_RGB_EXT, VK_BLEND_OP_INVERT_RGB_EXT>,
		EnumValuePair<EnumType::LINEARDODGE_EXT, VK_BLEND_OP_LINEARDODGE_EXT>,
		EnumValuePair<EnumType::LINEARBURN_EXT, VK_BLEND_OP_LINEARBURN_EXT>,
		EnumValuePair<EnumType::VIVIDLIGHT_EXT, VK_BLEND_OP_VIVIDLIGHT_EXT>,
		EnumValuePair<EnumType::LINEARLIGHT_EXT, VK_BLEND_OP_LINEARLIGHT_EXT>,
		EnumValuePair<EnumType::PINLIGHT_EXT, VK_BLEND_OP_PINLIGHT_EXT>,
		EnumValuePair<EnumType::HARDMIX_EXT, VK_BLEND_OP_HARDMIX_EXT>,
		EnumValuePair<EnumType::HSL_HUE_EXT, VK_BLEND_OP_HSL_HUE_EXT>,
		EnumValuePair<EnumType::HSL_SATURATION_EXT, VK_BLEND_OP_HSL_SATURATION_EXT>,
		EnumValuePair<EnumType::HSL_COLOR_EXT, VK_BLEND_OP_HSL_COLOR_EXT>,
		EnumValuePair<EnumType::HSL_LUMINOSITY_EXT, VK_BLEND_OP_HSL_LUMINOSITY_EXT>,
		EnumValuePair<EnumType::PLUS_EXT, VK_BLEND_OP_PLUS_EXT>,
		EnumValuePair<EnumType::PLUS_CLAMPED_EXT, VK_BLEND_OP_PLUS_CLAMPED_EXT>,
		EnumValuePair<EnumType::PLUS_CLAMPED_ALPHA_EXT, VK_BLEND_OP_PLUS_CLAMPED_ALPHA_EXT>,
		EnumValuePair<EnumType::PLUS_DARKER_EXT, VK_BLEND_OP_PLUS_DARKER_EXT>,
		EnumValuePair<EnumType::MINUS_EXT, VK_BLEND_OP_MINUS_EXT>,
		EnumValuePair<EnumType::MINUS_CLAMPED_EXT, VK_BLEND_OP_MINUS_CLAMPED_EXT>,
		EnumValuePair<EnumType::CONTRAST_EXT, VK_BLEND_OP_CONTRAST_EXT>,
		EnumValuePair<EnumType::INVERT_OVG_EXT, VK_BLEND_OP_INVERT_OVG_EXT>,
		EnumValuePair<EnumType::RED_EXT, VK_BLEND_OP_RED_EXT>,
		EnumValuePair<EnumType::GREEN_EXT, VK_BLEND_OP_GREEN_EXT>,
		EnumValuePair<EnumType::BLUE_EXT, VK_BLEND_OP_BLUE_EXT>
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

// Note: DirectX 12 doesn't have dynamic state like Vulkan
// Most state is set during PSO creation
template <>
struct orhi::utils::MappingFor<orhi::types::EDynamicState, UINT>
{
	using EnumType = orhi::types::EDynamicState;
	using type = std::tuple<
		EnumValuePair<EnumType::VIEWPORT, 0>, // Always dynamic in DX12
		EnumValuePair<EnumType::SCISSOR, 1>, // Always dynamic in DX12
		EnumValuePair<EnumType::BLEND_CONSTANTS, 2>, // Can be set per command list
		EnumValuePair<EnumType::STENCIL_REFERENCE, 3> // Can be set per command list
	>;
};

template <>
struct orhi::utils::MappingFor<orhi::types::EDescriptorPoolCreateFlags, VkDescriptorPoolCreateFlags>
{
	using EnumType = orhi::types::EDescriptorPoolCreateFlags;
	using type = std::tuple<
		EnumValuePair<EnumType::NONE, 0>,
		EnumValuePair<EnumType::FREE_DESCRIPTOR_SET_BIT, VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT>,
		EnumValuePair<EnumType::UPDATE_AFTER_BIND_BIT, VK_DESCRIPTOR_POOL_CREATE_UPDATE_AFTER_BIND_BIT>,
		EnumValuePair<EnumType::HOST_ONLY_BIT_EXT, VK_DESCRIPTOR_POOL_CREATE_HOST_ONLY_BIT_EXT>,
		EnumValuePair<EnumType::ALLOW_OVERALLOCATION_SETS_BIT_NV, VK_DESCRIPTOR_POOL_CREATE_ALLOW_OVERALLOCATION_SETS_BIT_NV>,
		EnumValuePair<EnumType::ALLOW_OVERALLOCATION_POOLS_BIT_NV, VK_DESCRIPTOR_POOL_CREATE_ALLOW_OVERALLOCATION_POOLS_BIT_NV>,
		EnumValuePair<EnumType::UPDATE_AFTER_BIND_BIT_EXT, VK_DESCRIPTOR_POOL_CREATE_UPDATE_AFTER_BIND_BIT_EXT>,
		EnumValuePair<EnumType::HOST_ONLY_BIT_VALVE, VK_DESCRIPTOR_POOL_CREATE_HOST_ONLY_BIT_VALVE>
	>;
};

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

// DX12 don't have this?
template <>
struct orhi::utils::MappingFor<orhi::types::ETextureTiling, VkImageTiling>
{
	using EnumType = orhi::types::ETextureTiling;
	using type = std::tuple<
		EnumValuePair<EnumType::OPTIMAL, VK_IMAGE_TILING_OPTIMAL>,
		EnumValuePair<EnumType::LINEAR, VK_IMAGE_TILING_LINEAR>
	>;
};

template <>
struct orhi::utils::MappingFor<orhi::types::ETextureLayout, VkImageLayout>
{
	using EnumType = orhi::types::ETextureLayout;
	using type = std::tuple<
		EnumValuePair<EnumType::UNDEFINED, VK_IMAGE_LAYOUT_UNDEFINED>,
		EnumValuePair<EnumType::GENERAL, VK_IMAGE_LAYOUT_GENERAL>,
		EnumValuePair<EnumType::COLOR_ATTACHMENT_OPTIMAL, VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL>,
		EnumValuePair<EnumType::DEPTH_STENCIL_ATTACHMENT_OPTIMAL, VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL>,
		EnumValuePair<EnumType::DEPTH_STENCIL_READ_ONLY_OPTIMAL, VK_IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL>,
		EnumValuePair<EnumType::SHADER_READ_ONLY_OPTIMAL, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL>,
		EnumValuePair<EnumType::TRANSFER_SRC_OPTIMAL, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL>,
		EnumValuePair<EnumType::TRANSFER_DST_OPTIMAL, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL>,
		EnumValuePair<EnumType::PREINITIALIZED, VK_IMAGE_LAYOUT_PREINITIALIZED>,
		EnumValuePair<EnumType::DEPTH_READ_ONLY_STENCIL_ATTACHMENT_OPTIMAL, VK_IMAGE_LAYOUT_DEPTH_READ_ONLY_STENCIL_ATTACHMENT_OPTIMAL>,
		EnumValuePair<EnumType::DEPTH_ATTACHMENT_STENCIL_READ_ONLY_OPTIMAL, VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_STENCIL_READ_ONLY_OPTIMAL>,
		EnumValuePair<EnumType::DEPTH_ATTACHMENT_OPTIMAL, VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_OPTIMAL>,
		EnumValuePair<EnumType::DEPTH_READ_ONLY_OPTIMAL, VK_IMAGE_LAYOUT_DEPTH_READ_ONLY_OPTIMAL>,
		EnumValuePair<EnumType::STENCIL_ATTACHMENT_OPTIMAL, VK_IMAGE_LAYOUT_STENCIL_ATTACHMENT_OPTIMAL>,
		EnumValuePair<EnumType::STENCIL_READ_ONLY_OPTIMAL, VK_IMAGE_LAYOUT_STENCIL_READ_ONLY_OPTIMAL>,
		EnumValuePair<EnumType::READ_ONLY_OPTIMAL, VK_IMAGE_LAYOUT_READ_ONLY_OPTIMAL>,
		EnumValuePair<EnumType::ATTACHMENT_OPTIMAL, VK_IMAGE_LAYOUT_ATTACHMENT_OPTIMAL>,
		EnumValuePair<EnumType::PRESENT_SRC_KHR, VK_IMAGE_LAYOUT_PRESENT_SRC_KHR>
	>;
};

// DX12 has enums 
template <>
struct orhi::utils::MappingFor<orhi::types::EFilter, D3D12_FILTER_TYPE>
{
	using EnumType = orhi::types::EFilter;
	using type = std::tuple<
		EnumValuePair<EnumType::NEAREST, D3D12_FILTER_TYPE_POINT>,
		EnumValuePair<EnumType::LINEAR, D3D12_FILTER_TYPE_LINEAR>
	>;
};

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

template <>
struct orhi::utils::MappingFor<orhi::types::ESamplerMipmapMode, VkSamplerMipmapMode>
{
	using EnumType = orhi::types::ESamplerMipmapMode;
	using type = std::tuple<
		EnumValuePair<EnumType::NEAREST, VK_SAMPLER_MIPMAP_MODE_NEAREST>,
		EnumValuePair<EnumType::LINEAR, VK_SAMPLER_MIPMAP_MODE_LINEAR>
	>;
};

template <>
struct orhi::utils::MappingFor<orhi::types::ETextureAspectFlags, VkImageAspectFlags>
{
	using EnumType = orhi::types::ETextureAspectFlags;
	using type = std::tuple<
		EnumValuePair<EnumType::COLOR, VK_IMAGE_ASPECT_COLOR_BIT>,
		EnumValuePair<EnumType::DEPTH, VK_IMAGE_ASPECT_DEPTH_BIT>,
		EnumValuePair<EnumType::STENCIL, VK_IMAGE_ASPECT_STENCIL_BIT>
	>;
};

#endif // #if defined(ORHI_COMPILE_DX12)
