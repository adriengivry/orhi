/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#if defined(ORHI_COMPILE_MOCK)

#include <orhi/debug/Assert.h>
#include <orhi/debug/Log.h>
#include <orhi/impl/mock/Backend.h>

using namespace orhi::impl::mock;

namespace orhi
{
	template<>
	std::optional<orhi::data::PipelineState> Backend::Init(bool debug)
	{
		ORHI_LOG_INFO("Mock backend initialized.");

		return orhi::data::PipelineState{};
	}

	template<>
	void Backend::Clear(bool p_colorBuffer, bool p_depthBuffer, bool p_stencilBuffer)
	{}

	template<>
	void Backend::DrawElements(types::EPrimitiveMode p_primitiveMode, uint32_t p_indexCount)
	{}

	template<>
	void Backend::DrawElementsInstanced(types::EPrimitiveMode p_primitiveMode, uint32_t p_indexCount, uint32_t p_instances)
	{}

	template<>
	void Backend::DrawArrays(types::EPrimitiveMode p_primitiveMode, uint32_t p_vertexCount)
	{}

	template<>
	void Backend::DrawArraysInstanced(types::EPrimitiveMode p_primitiveMode, uint32_t p_vertexCount, uint32_t p_instances)
	{}

	template<>
	void Backend::DispatchCompute(uint32_t p_x, uint32_t p_y, uint32_t p_z) const
	{
		ORHI_ASSERT(
			p_x > 0 && p_y > 0 && p_z > 0,
			"Dispatch work group count cannot be zero"
		);
	}

	template<>
	void Backend::MemoryBarrier(types::EMemoryBarrierFlags p_barriers) const
	{}

	template<>
	void Backend::SetClearColor(float p_red, float p_green, float p_blue, float p_alpha)
	{}

	template<>
	void Backend::SetRasterizationLinesWidth(float p_width)
	{}

	template<>
	void Backend::SetRasterizationMode(types::ERasterizationMode p_rasterizationMode)
	{}

	template<>
	void Backend::SetCapability(types::ERenderingCapability p_capability, bool p_value)
	{}

	template<>
	bool Backend::GetCapability(types::ERenderingCapability p_capability)
	{
		return false;
	}

	template<>
	void Backend::SetStencilAlgorithm(types::EComparaisonAlgorithm p_algorithm, int32_t p_reference, uint32_t p_mask)
	{}

	template<>
	void Backend::SetDepthAlgorithm(types::EComparaisonAlgorithm p_algorithm)
	{}

	template<>
	void Backend::SetStencilMask(uint32_t p_mask)
	{}

	template<>
	void Backend::SetStencilOperations(types::EOperation p_stencilFail, types::EOperation p_depthFail, types::EOperation p_bothPass)
	{}

	template<>
	void Backend::SetBlendingFunction(types::EBlendingFactor p_sourceFactor, types::EBlendingFactor p_destinationFactor)
	{}

	template<>
	void Backend::SetBlendingEquation(types::EBlendingEquation p_equation)
	{}

	template<>
	void Backend::SetCullFace(types::ECullFace p_cullFace)
	{}

	template<>
	void Backend::SetDepthWriting(bool p_enable)
	{}

	template<>
	void Backend::SetColorWriting(bool p_enableRed, bool p_enableGreen, bool p_enableBlue, bool p_enableAlpha)
	{}

	template<>
	void Backend::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
	{}

	template<>
	std::string Backend::GetVendor()
	{
		return "None";
	}

	template<>
	std::string Backend::GetHardware()
	{
		return "None";
	}

	template<>
	std::string Backend::GetVersion()
	{
		return "None";
	}

	template<>
	std::string Backend::GetShadingLanguageVersion()
	{
		return "None";
	}
}

#endif // #if defined(ORHI_COMPILE_MOCK)
