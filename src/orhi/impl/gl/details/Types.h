/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#if defined(ORHI_COMPILE_OPENGL)

#include <orhi/impl/gl/details/glad/glad.h>
#include <orhi/types/EAccessSpecifier.h>
#include <orhi/types/EBlendingEquation.h>
#include <orhi/types/EBlendingFactor.h>
#include <orhi/types/EBufferType.h>
#include <orhi/types/EComparaisonAlgorithm.h>
#include <orhi/types/ECullFace.h>
#include <orhi/types/EDataType.h>
#include <orhi/types/EFormat.h>
#include <orhi/types/EFramebufferAttachment.h>
#include <orhi/types/EInternalFormat.h>
#include <orhi/types/EMemoryBarrierFlags.h>
#include <orhi/types/EOperation.h>
#include <orhi/types/EPrimitiveMode.h>
#include <orhi/types/ERasterizationMode.h>
#include <orhi/types/ERenderingCapability.h>
#include <orhi/types/EShaderType.h>
#include <orhi/types/ETextureFilteringMode.h>
#include <orhi/types/ETextureType.h>
#include <orhi/types/ETextureWrapMode.h>
#include <orhi/types/EUniformType.h>
#include <orhi/types/EPixelDataFormat.h>
#include <orhi/types/EPixelDataType.h>
#include <orhi/utils/EnumMapper.h>

template <>
struct orhi::utils::MappingFor<orhi::types::EComparaisonAlgorithm, GLenum>
{
	using EnumType = orhi::types::EComparaisonAlgorithm;
	using type = std::tuple<
		EnumValuePair<EnumType::NEVER, GL_NEVER>,
		EnumValuePair<EnumType::LESS, GL_LESS>,
		EnumValuePair<EnumType::EQUAL, GL_EQUAL>,
		EnumValuePair<EnumType::LESS_EQUAL, GL_LEQUAL>,
		EnumValuePair<EnumType::GREATER, GL_GREATER>,
		EnumValuePair<EnumType::NOTEQUAL, GL_NOTEQUAL>,
		EnumValuePair<EnumType::GREATER_EQUAL, GL_GEQUAL>,
		EnumValuePair<EnumType::ALWAYS, GL_ALWAYS>
	>;
};

template <>
struct orhi::utils::MappingFor<orhi::types::EBlendingEquation, GLenum>
{
	using EnumType = orhi::types::EBlendingEquation;
	using type = std::tuple<
		EnumValuePair<EnumType::FUNC_ADD, GL_FUNC_ADD>,
		EnumValuePair<EnumType::FUNC_SUBTRACT, GL_FUNC_SUBTRACT>,
		EnumValuePair<EnumType::FUNC_REVERSE_SUBTRACT, GL_FUNC_REVERSE_SUBTRACT>,
		EnumValuePair<EnumType::MIN, GL_MIN>,
		EnumValuePair<EnumType::MAX, GL_MAX>
	>;
};

template <>
struct orhi::utils::MappingFor<orhi::types::EBlendingFactor, GLenum>
{
	using EnumType = orhi::types::EBlendingFactor;
	using type = std::tuple<
		EnumValuePair<EnumType::ZERO, GL_ZERO>,
		EnumValuePair<EnumType::ONE, GL_ONE>,
		EnumValuePair<EnumType::SRC_COLOR, GL_SRC_COLOR>,
		EnumValuePair<EnumType::ONE_MINUS_SRC_COLOR, GL_ONE_MINUS_SRC_COLOR>,
		EnumValuePair<EnumType::DST_COLOR, GL_DST_COLOR>,
		EnumValuePair<EnumType::ONE_MINUS_DST_COLOR, GL_ONE_MINUS_DST_COLOR>,
		EnumValuePair<EnumType::SRC_ALPHA, GL_SRC_ALPHA>,
		EnumValuePair<EnumType::ONE_MINUS_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA>,
		EnumValuePair<EnumType::DST_ALPHA, GL_DST_ALPHA>,
		EnumValuePair<EnumType::ONE_MINUS_DST_ALPHA, GL_ONE_MINUS_DST_ALPHA>,
		EnumValuePair<EnumType::CONSTANT_COLOR, GL_CONSTANT_COLOR>,
		EnumValuePair<EnumType::ONE_MINUS_CONSTANT_COLOR, GL_ONE_MINUS_CONSTANT_COLOR>,
		EnumValuePair<EnumType::CONSTANT_ALPHA, GL_CONSTANT_ALPHA>,
		EnumValuePair<EnumType::ONE_MINUS_CONSTANT_ALPHA, GL_ONE_MINUS_CONSTANT_ALPHA>,
		EnumValuePair<EnumType::SRC_ALPHA_SATURATE, GL_SRC_ALPHA_SATURATE>,
		EnumValuePair<EnumType::SRC1_COLOR, GL_SRC1_COLOR>,
		EnumValuePair<EnumType::ONE_MINUS_SRC1_COLOR, GL_ONE_MINUS_SRC1_COLOR>,
		EnumValuePair<EnumType::SRC1_ALPHA, GL_SRC1_ALPHA>,
		EnumValuePair<EnumType::ONE_MINUS_SRC1_ALPHA, GL_ONE_MINUS_SRC1_ALPHA>
	>;
};

template <>
struct orhi::utils::MappingFor<orhi::types::ERasterizationMode, GLenum>
{
	using EnumType = orhi::types::ERasterizationMode;
	using type = std::tuple<
		EnumValuePair<EnumType::POINT, GL_POINT>,
		EnumValuePair<EnumType::LINE, GL_LINE>,
		EnumValuePair<EnumType::FILL, GL_FILL>
	>;
};

template <>
struct orhi::utils::MappingFor<orhi::types::ECullFace, GLenum>
{
	using EnumType = orhi::types::ECullFace;
	using type = std::tuple<
		EnumValuePair<EnumType::FRONT, GL_FRONT>,
		EnumValuePair<EnumType::BACK, GL_BACK>,
		EnumValuePair<EnumType::FRONT_AND_BACK, GL_FRONT_AND_BACK>
	>;
};

template <>
struct orhi::utils::MappingFor<orhi::types::EOperation, GLenum>
{
	using EnumType = orhi::types::EOperation;
	using type = std::tuple<
		EnumValuePair<EnumType::KEEP, GL_KEEP>,
		EnumValuePair<EnumType::ZERO, GL_ZERO>,
		EnumValuePair<EnumType::REPLACE, GL_REPLACE>,
		EnumValuePair<EnumType::INCREMENT, GL_INCR>,
		EnumValuePair<EnumType::INCREMENT_WRAP, GL_INCR_WRAP>,
		EnumValuePair<EnumType::DECREMENT, GL_DECR>,
		EnumValuePair<EnumType::DECREMENT_WRAP, GL_DECR_WRAP>,
		EnumValuePair<EnumType::INVERT, GL_INVERT>
	>;
};

template <>
struct orhi::utils::MappingFor<orhi::types::ERenderingCapability, GLenum>
{
	using EnumType = orhi::types::ERenderingCapability;
	using type = std::tuple<
		EnumValuePair<EnumType::BLEND, GL_BLEND>,
		EnumValuePair<EnumType::CULL_FACE, GL_CULL_FACE>,
		EnumValuePair<EnumType::DEPTH_TEST, GL_DEPTH_TEST>,
		EnumValuePair<EnumType::DITHER, GL_DITHER>,
		EnumValuePair<EnumType::POLYGON_OFFSET_FILL, GL_POLYGON_OFFSET_FILL>,
		EnumValuePair<EnumType::SAMPLE_ALPHA_TO_COVERAGE, GL_SAMPLE_ALPHA_TO_COVERAGE>,
		EnumValuePair<EnumType::SAMPLE_COVERAGE, GL_SAMPLE_COVERAGE>,
		EnumValuePair<EnumType::SCISSOR_TEST, GL_SCISSOR_TEST>,
		EnumValuePair<EnumType::STENCIL_TEST, GL_STENCIL_TEST>,
		EnumValuePair<EnumType::MULTISAMPLE, GL_MULTISAMPLE>
	>;
};

template <>
struct orhi::utils::MappingFor<orhi::types::EPrimitiveMode, GLenum>
{
	using EnumType = orhi::types::EPrimitiveMode;
	using type = std::tuple<
		EnumValuePair<EnumType::POINTS, GL_POINTS>,
		EnumValuePair<EnumType::LINES, GL_LINES>,
		EnumValuePair<EnumType::LINE_LOOP, GL_LINE_LOOP>,
		EnumValuePair<EnumType::LINE_STRIP, GL_LINE_STRIP>,
		EnumValuePair<EnumType::TRIANGLES, GL_TRIANGLES>,
		EnumValuePair<EnumType::TRIANGLE_STRIP, GL_TRIANGLE_STRIP>,
		EnumValuePair<EnumType::TRIANGLE_FAN, GL_TRIANGLE_FAN>,
		EnumValuePair<EnumType::LINES_ADJACENCY, GL_LINES_ADJACENCY>,
		EnumValuePair<EnumType::LINE_STRIP_ADJACENCY, GL_LINE_STRIP_ADJACENCY>,
		EnumValuePair<EnumType::PATCHES, GL_PATCHES>
	>;
};

template <>
struct orhi::utils::MappingFor<orhi::types::EFormat, GLenum>
{
	using EnumType = orhi::types::EFormat;
	using type = std::tuple<
		EnumValuePair<EnumType::RED, GL_RED>,
		EnumValuePair<EnumType::RG, GL_RG>,
		EnumValuePair<EnumType::RGB, GL_RGB>,
		EnumValuePair<EnumType::BGR, GL_BGR>,
		EnumValuePair<EnumType::RGBA, GL_RGBA>,
		EnumValuePair<EnumType::BGRA, GL_BGRA>,
		EnumValuePair<EnumType::RED_INTEGER, GL_RED_INTEGER>,
		EnumValuePair<EnumType::RG_INTEGER, GL_RG_INTEGER>,
		EnumValuePair<EnumType::RGB_INTEGER, GL_RGB_INTEGER>,
		EnumValuePair<EnumType::BGR_INTEGER, GL_BGR_INTEGER>,
		EnumValuePair<EnumType::RGBA_INTEGER, GL_RGBA_INTEGER>,
		EnumValuePair<EnumType::BGRA_INTEGER, GL_BGRA_INTEGER>,
		EnumValuePair<EnumType::STENCIL_INDEX, GL_STENCIL_INDEX>,
		EnumValuePair<EnumType::DEPTH_COMPONENT, GL_DEPTH_COMPONENT>,
		EnumValuePair<EnumType::DEPTH_STENCIL, GL_DEPTH_STENCIL>
	>;
};

template <>
struct orhi::utils::MappingFor<orhi::types::ETextureFilteringMode, GLenum>
{
	using EnumType = orhi::types::ETextureFilteringMode;
	using type = std::tuple<
		EnumValuePair<EnumType::NEAREST, GL_NEAREST>,
		EnumValuePair<EnumType::LINEAR, GL_LINEAR>,
		EnumValuePair<EnumType::NEAREST_MIPMAP_NEAREST, GL_NEAREST_MIPMAP_NEAREST>,
		EnumValuePair<EnumType::LINEAR_MIPMAP_LINEAR, GL_LINEAR_MIPMAP_LINEAR>,
		EnumValuePair<EnumType::LINEAR_MIPMAP_NEAREST, GL_LINEAR_MIPMAP_NEAREST>,
		EnumValuePair<EnumType::NEAREST_MIPMAP_LINEAR, GL_NEAREST_MIPMAP_LINEAR>
	>;
};

template <>
struct orhi::utils::MappingFor<orhi::types::ETextureWrapMode, GLenum>
{
	using EnumType = orhi::types::ETextureWrapMode;
	using type = std::tuple<
		EnumValuePair<EnumType::REPEAT, GL_REPEAT>,
		EnumValuePair<EnumType::CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE>,
		EnumValuePair<EnumType::CLAMP_TO_BORDER, GL_CLAMP_TO_BORDER>,
		EnumValuePair<EnumType::MIRRORED_REPEAT, GL_MIRRORED_REPEAT>,
		EnumValuePair<EnumType::MIRROR_CLAMP_TO_EDGE, GL_MIRROR_CLAMP_TO_EDGE>
	>;
};

template <>
struct orhi::utils::MappingFor<orhi::types::EPixelDataFormat, GLenum>
{
	using EnumType = orhi::types::EPixelDataFormat;
	using type = std::tuple<
		EnumValuePair<EnumType::STENCIL_INDEX, GL_STENCIL_INDEX>,
		EnumValuePair<EnumType::DEPTH_COMPONENT, GL_DEPTH_COMPONENT>,
		EnumValuePair<EnumType::RED, GL_RED>,
		EnumValuePair<EnumType::GREEN, GL_GREEN>,
		EnumValuePair<EnumType::BLUE, GL_BLUE>,
		EnumValuePair<EnumType::ALPHA, GL_ALPHA>,
		EnumValuePair<EnumType::RGB, GL_RGB>,
		EnumValuePair<EnumType::BGR, GL_BGR>,
		EnumValuePair<EnumType::RGBA, GL_RGBA>,
		EnumValuePair<EnumType::BGRA, GL_BGRA>
	>;
};

template <>
struct orhi::utils::MappingFor<orhi::types::EPixelDataType, GLenum>
{
	using EnumType = orhi::types::EPixelDataType;
	using type = std::tuple<
		EnumValuePair<EnumType::BYTE, GL_BYTE>,
		EnumValuePair<EnumType::UNSIGNED_BYTE, GL_UNSIGNED_BYTE>,
		EnumValuePair<EnumType::SHORT, GL_SHORT>,
		EnumValuePair<EnumType::UNSIGNED_SHORT, GL_UNSIGNED_SHORT>,
		EnumValuePair<EnumType::INT, GL_INT>,
		EnumValuePair<EnumType::UNSIGNED_INT, GL_UNSIGNED_INT>,
		EnumValuePair<EnumType::FLOAT, GL_FLOAT>,
		EnumValuePair<EnumType::UNSIGNED_BYTE_3_3_2, GL_UNSIGNED_BYTE_3_3_2>,
		EnumValuePair<EnumType::UNSIGNED_BYTE_2_3_3_REV, GL_UNSIGNED_BYTE_2_3_3_REV>,
		EnumValuePair<EnumType::UNSIGNED_SHORT_5_6_5, GL_UNSIGNED_SHORT_5_6_5>,
		EnumValuePair<EnumType::UNSIGNED_SHORT_5_6_5_REV, GL_UNSIGNED_SHORT_5_6_5_REV>,
		EnumValuePair<EnumType::UNSIGNED_SHORT_4_4_4_4, GL_UNSIGNED_SHORT_4_4_4_4>,
		EnumValuePair<EnumType::UNSIGNED_SHORT_4_4_4_4_REV, GL_UNSIGNED_SHORT_4_4_4_4_REV>,
		EnumValuePair<EnumType::UNSIGNED_SHORT_5_5_5_1, GL_UNSIGNED_SHORT_5_5_5_1>,
		EnumValuePair<EnumType::UNSIGNED_SHORT_1_5_5_5_REV, GL_UNSIGNED_SHORT_1_5_5_5_REV>,
		EnumValuePair<EnumType::UNSIGNED_INT_8_8_8_8, GL_UNSIGNED_INT_8_8_8_8>,
		EnumValuePair<EnumType::UNSIGNED_INT_8_8_8_8_REV, GL_UNSIGNED_INT_8_8_8_8_REV>,
		EnumValuePair<EnumType::UNSIGNED_INT_10_10_10_2, GL_UNSIGNED_INT_10_10_10_2>,
		EnumValuePair<EnumType::UNSIGNED_INT_2_10_10_10_REV, GL_UNSIGNED_INT_2_10_10_10_REV>
	>;
};

template <>
struct orhi::utils::MappingFor<orhi::types::EDataType, GLenum>
{
	using EnumType = orhi::types::EDataType;
	using type = std::tuple<
		EnumValuePair<EnumType::BYTE, GL_BYTE>,
		EnumValuePair<EnumType::UNSIGNED_BYTE, GL_UNSIGNED_BYTE>,
		EnumValuePair<EnumType::SHORT, GL_SHORT>,
		EnumValuePair<EnumType::UNSIGNED_SHORT, GL_UNSIGNED_SHORT>,
		EnumValuePair<EnumType::INT, GL_INT>,
		EnumValuePair<EnumType::UNSIGNED_INT, GL_UNSIGNED_INT>,
		EnumValuePair<EnumType::FLOAT, GL_FLOAT>,
		EnumValuePair<EnumType::DOUBLE, GL_DOUBLE>
	>;
};

template <>
struct orhi::utils::MappingFor<orhi::types::EAccessSpecifier, GLenum>
{
	using EnumType = orhi::types::EAccessSpecifier;
	using type = std::tuple<
		EnumValuePair<EnumType::STREAM_DRAW, GL_STREAM_DRAW>,
		EnumValuePair<EnumType::STREAM_READ, GL_STREAM_READ>,
		EnumValuePair<EnumType::STREAM_COPY, GL_STREAM_COPY>,
		EnumValuePair<EnumType::DYNAMIC_DRAW, GL_DYNAMIC_DRAW>,
		EnumValuePair<EnumType::DYNAMIC_READ, GL_DYNAMIC_READ>,
		EnumValuePair<EnumType::DYNAMIC_COPY, GL_DYNAMIC_COPY>,
		EnumValuePair<EnumType::STATIC_DRAW, GL_STATIC_DRAW>,
		EnumValuePair<EnumType::STATIC_READ, GL_STATIC_READ>,
		EnumValuePair<EnumType::STATIC_COPY, GL_STATIC_COPY>
	>;
};

template <>
struct orhi::utils::MappingFor<orhi::types::EUniformType, GLenum>
{
	using EnumType = orhi::types::EUniformType;
	using type = std::tuple<
		EnumValuePair<EnumType::BOOL, GL_BOOL>,
		EnumValuePair<EnumType::INT, GL_INT>,
		EnumValuePair<EnumType::FLOAT, GL_FLOAT>,
		EnumValuePair<EnumType::FLOAT_VEC2, GL_FLOAT_VEC2>,
		EnumValuePair<EnumType::FLOAT_VEC3, GL_FLOAT_VEC3>,
		EnumValuePair<EnumType::FLOAT_VEC4, GL_FLOAT_VEC4>,
		EnumValuePair<EnumType::FLOAT_MAT3, GL_FLOAT_MAT3>,
		EnumValuePair<EnumType::FLOAT_MAT4, GL_FLOAT_MAT4>,
		EnumValuePair<EnumType::DOUBLE_MAT4, GL_DOUBLE_MAT4>,
		EnumValuePair<EnumType::SAMPLER_2D, GL_SAMPLER_2D>,
		EnumValuePair<EnumType::SAMPLER_CUBE, GL_SAMPLER_CUBE>
	>;
};

template <>
struct orhi::utils::MappingFor<orhi::types::EInternalFormat, GLenum>
{
	using EnumType = orhi::types::EInternalFormat;
	using type = std::tuple <
		EnumValuePair<EnumType::DEPTH_COMPONENT, GL_DEPTH_COMPONENT>,
		EnumValuePair<EnumType::DEPTH_STENCIL, GL_DEPTH_STENCIL>,
		EnumValuePair<EnumType::RED, GL_RED>,
		EnumValuePair<EnumType::RG, GL_RG>,
		EnumValuePair<EnumType::RGB, GL_RGB>,
		EnumValuePair<EnumType::RGBA, GL_RGBA>,
		EnumValuePair<EnumType::R8, GL_R8>,
		EnumValuePair<EnumType::R8_SNORM, GL_R8_SNORM>,
		EnumValuePair<EnumType::R16, GL_R16>,
		EnumValuePair<EnumType::R16_SNORM, GL_R16_SNORM>,
		EnumValuePair<EnumType::RG8, GL_RG8>,
		EnumValuePair<EnumType::RG8_SNORM, GL_RG8_SNORM>,
		EnumValuePair<EnumType::RG16, GL_RG16>,
		EnumValuePair<EnumType::RG16_SNORM, GL_RG16_SNORM>,
		EnumValuePair<EnumType::R3_G3_B2, GL_R3_G3_B2>,
		EnumValuePair<EnumType::RGB4, GL_RGB4>,
		EnumValuePair<EnumType::RGB5, GL_RGB5>,
		EnumValuePair<EnumType::RGB8, GL_RGB8>,
		EnumValuePair<EnumType::RGB8_SNORM, GL_RGB8_SNORM>,
		EnumValuePair<EnumType::RGB10, GL_RGB10>,
		EnumValuePair<EnumType::RGB12, GL_RGB12>,
		EnumValuePair<EnumType::RGB16_SNORM, GL_RGB16_SNORM>,
		EnumValuePair<EnumType::RGBA2, GL_RGBA2>,
		EnumValuePair<EnumType::RGBA4, GL_RGBA4>,
		EnumValuePair<EnumType::RGB5_A1, GL_RGB5_A1>,
		EnumValuePair<EnumType::RGBA8, GL_RGBA8>,
		EnumValuePair<EnumType::RGBA8_SNORM, GL_RGBA8_SNORM>,
		EnumValuePair<EnumType::RGB10_A2, GL_RGB10_A2>,
		EnumValuePair<EnumType::RGB10_A2UI, GL_RGB10_A2UI>,
		EnumValuePair<EnumType::RGBA12, GL_RGBA12>,
		EnumValuePair<EnumType::RGBA16, GL_RGBA16>,
		EnumValuePair<EnumType::SRGB8, GL_SRGB8>,
		EnumValuePair<EnumType::SRGB8_ALPHA8, GL_SRGB8_ALPHA8>,
		EnumValuePair<EnumType::R16F, GL_R16F>,
		EnumValuePair<EnumType::RG16F, GL_RG16F>,
		EnumValuePair<EnumType::RGB16F, GL_RGB16F>,
		EnumValuePair<EnumType::RGBA16F, GL_RGBA16F>,
		EnumValuePair<EnumType::R32F, GL_R32F>,
		EnumValuePair<EnumType::RG32F, GL_RG32F>,
		EnumValuePair<EnumType::RGB32F, GL_RGB32F>,
		EnumValuePair<EnumType::RGBA32F, GL_RGBA32F>,
		EnumValuePair<EnumType::R11F_G11F_B10F, GL_R11F_G11F_B10F>,
		EnumValuePair<EnumType::RGB9_E5, GL_RGB9_E5>,
		EnumValuePair<EnumType::R8I, GL_R8I>,
		EnumValuePair<EnumType::R8UI, GL_R8UI>,
		EnumValuePair<EnumType::R16I, GL_R16I>,
		EnumValuePair<EnumType::R16UI, GL_R16UI>,
		EnumValuePair<EnumType::R32I, GL_R32I>,
		EnumValuePair<EnumType::R32UI, GL_R32UI>,
		EnumValuePair<EnumType::RG8I, GL_RG8I>,
		EnumValuePair<EnumType::RG8UI, GL_RG8UI>,
		EnumValuePair<EnumType::RG16I, GL_RG16I>,
		EnumValuePair<EnumType::RG16UI, GL_RG16UI>,
		EnumValuePair<EnumType::RG32I, GL_RG32I>,
		EnumValuePair<EnumType::RG32UI, GL_RG32UI>,
		EnumValuePair<EnumType::RGB8I, GL_RGB8I>,
		EnumValuePair<EnumType::RGB8UI, GL_RGB8UI>,
		EnumValuePair<EnumType::RGB16I, GL_RGB16I>,
		EnumValuePair<EnumType::RGB16UI, GL_RGB16UI>,
		EnumValuePair<EnumType::RGB32I, GL_RGB32I>,
		EnumValuePair<EnumType::RGB32UI, GL_RGB32UI>,
		EnumValuePair<EnumType::RGBA8I, GL_RGBA8I>,
		EnumValuePair<EnumType::RGBA8UI, GL_RGBA8UI>,
		EnumValuePair<EnumType::RGBA16I, GL_RGBA16I>,
		EnumValuePair<EnumType::RGBA16UI, GL_RGBA16UI>,
		EnumValuePair<EnumType::RGBA32I, GL_RGBA32I>,
		EnumValuePair<EnumType::RGBA32UI, GL_RGBA32UI>,
		EnumValuePair<EnumType::COMPRESSED_RED, GL_COMPRESSED_RED>,
		EnumValuePair<EnumType::COMPRESSED_RG, GL_COMPRESSED_RG>,
		EnumValuePair<EnumType::COMPRESSED_RGB, GL_COMPRESSED_RGB>,
		EnumValuePair<EnumType::COMPRESSED_RGBA, GL_COMPRESSED_RGBA>,
		EnumValuePair<EnumType::COMPRESSED_SRGB, GL_COMPRESSED_SRGB>,
		EnumValuePair<EnumType::COMPRESSED_SRGB_ALPHA, GL_COMPRESSED_SRGB_ALPHA>,
		EnumValuePair<EnumType::COMPRESSED_RED_RGTC1, GL_COMPRESSED_RED_RGTC1>,
		EnumValuePair<EnumType::COMPRESSED_SIGNED_RED_RGTC1, GL_COMPRESSED_SIGNED_RED_RGTC1>,
		EnumValuePair<EnumType::COMPRESSED_RG_RGTC2, GL_COMPRESSED_RG_RGTC2>,
		EnumValuePair<EnumType::COMPRESSED_SIGNED_RG_RGTC2, GL_COMPRESSED_SIGNED_RG_RGTC2>,
		EnumValuePair<EnumType::COMPRESSED_RGBA_BPTC_UNORM, GL_COMPRESSED_RGBA_BPTC_UNORM>,
		EnumValuePair<EnumType::COMPRESSED_SRGB_ALPHA_BPTC_UNORM, GL_COMPRESSED_SRGB_ALPHA_BPTC_UNORM>,
		EnumValuePair<EnumType::COMPRESSED_RGB_BPTC_SIGNED_FLOAT, GL_COMPRESSED_RGB_BPTC_SIGNED_FLOAT>,
		EnumValuePair<EnumType::COMPRESSED_RGB_BPTC_UNSIGNED_FLOAT, GL_COMPRESSED_RGB_BPTC_UNSIGNED_FLOAT>
	>;
};

template <>
struct orhi::utils::MappingFor<orhi::types::EShaderType, GLenum>
{
	using EnumType = orhi::types::EShaderType;
	using type = std::tuple<
		EnumValuePair<EnumType::VERTEX, GL_VERTEX_SHADER>,
		EnumValuePair<EnumType::FRAGMENT, GL_FRAGMENT_SHADER>,
		EnumValuePair<EnumType::GEOMETRY, GL_GEOMETRY_SHADER>,
		EnumValuePair<EnumType::COMPUTE, GL_COMPUTE_SHADER>
	>;
};

template <>
struct orhi::utils::MappingFor<orhi::types::EFramebufferAttachment, GLenum>
{
	using EnumType = orhi::types::EFramebufferAttachment;
	using type = std::tuple<
		EnumValuePair<EnumType::COLOR, GL_COLOR_ATTACHMENT0>,
		EnumValuePair<EnumType::DEPTH, GL_DEPTH_ATTACHMENT>,
		EnumValuePair<EnumType::STENCIL, GL_STENCIL_ATTACHMENT>,
		EnumValuePair<EnumType::DEPTH_STENCIL, GL_DEPTH_STENCIL_ATTACHMENT>
	>;
};

template <>
struct orhi::utils::MappingFor<orhi::types::EBufferType, GLenum>
{
	using EnumType = orhi::types::EBufferType;
	using type = std::tuple<
		EnumValuePair<EnumType::VERTEX, GL_ARRAY_BUFFER>,
		EnumValuePair<EnumType::INDEX, GL_ELEMENT_ARRAY_BUFFER>,
		EnumValuePair<EnumType::UNIFORM, GL_UNIFORM_BUFFER>,
		EnumValuePair<EnumType::SHADER_STORAGE, GL_SHADER_STORAGE_BUFFER>
	>;
};

template <>
struct orhi::utils::MappingFor<orhi::types::ETextureType, GLenum>
{
	using EnumType = orhi::types::ETextureType;
	using type = std::tuple<
		EnumValuePair<EnumType::TEXTURE_2D, GL_TEXTURE_2D>,
		EnumValuePair<EnumType::TEXTURE_CUBE, GL_TEXTURE_CUBE_MAP>
	>;
};

template <>
struct orhi::utils::MappingFor<orhi::types::EMemoryBarrierFlags, GLbitfield>
{
	using EnumType = orhi::types::EMemoryBarrierFlags;
	using type = std::tuple<
		EnumValuePair<EnumType::VERTEX_ATTRIB_ARRAY, GL_VERTEX_ATTRIB_ARRAY_BARRIER_BIT>,
		EnumValuePair<EnumType::ELEMENT_ARRAY, GL_ELEMENT_ARRAY_BARRIER_BIT>,
		EnumValuePair<EnumType::UNIFORM, GL_UNIFORM_BARRIER_BIT>,
		EnumValuePair<EnumType::TEXTURE_FETCH, GL_TEXTURE_FETCH_BARRIER_BIT>,
		EnumValuePair<EnumType::SHADER_IMAGE_ACCESS, GL_SHADER_IMAGE_ACCESS_BARRIER_BIT>,
		EnumValuePair<EnumType::COMMAND, GL_COMMAND_BARRIER_BIT>,
		EnumValuePair<EnumType::PIXEL_BUFFER, GL_PIXEL_BUFFER_BARRIER_BIT>,
		EnumValuePair<EnumType::TEXTURE_UPDATE, GL_TEXTURE_UPDATE_BARRIER_BIT>,
		EnumValuePair<EnumType::BUFFER_UPDATE, GL_BUFFER_UPDATE_BARRIER_BIT>,
		EnumValuePair<EnumType::CLIENT_MAPPED_BUFFER, GL_CLIENT_MAPPED_BUFFER_BARRIER_BIT>,
		EnumValuePair<EnumType::FRAMEBUFFER, GL_FRAMEBUFFER_BARRIER_BIT>,
		EnumValuePair<EnumType::TRANSFORM_FEEDBACK, GL_TRANSFORM_FEEDBACK_BARRIER_BIT>,
		EnumValuePair<EnumType::ATOMIC_COUNTER, GL_ATOMIC_COUNTER_BARRIER_BIT>,
		EnumValuePair<EnumType::SHADER_STORAGE, GL_SHADER_STORAGE_BARRIER_BIT>,
		EnumValuePair<EnumType::QUERY_BUFFER, GL_QUERY_BUFFER_BARRIER_BIT>,
		EnumValuePair<EnumType::ALL, GL_ALL_BARRIER_BITS>
	>;
};

#endif // #if defined(ORHI_COMPILE_OPENGL)
