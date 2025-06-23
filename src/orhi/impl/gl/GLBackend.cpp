/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#if defined(ORHI_COMPILE_OPENGL)

#include <format>

#include <orhi/data/PipelineState.h>
#include <orhi/debug/Log.h>
#include <orhi/debug/Assert.h>
#include <orhi/impl/gl/details/Types.h>
#include <orhi/impl/gl/details/glad/glad.h>
#include <orhi/impl/gl/Backend.h>
#include <orhi/math/Conversions.h>

using namespace orhi::impl::gl;

namespace
{
	void GLDebugMessageCallback(uint32_t source, uint32_t type, uint32_t id, uint32_t severity, int32_t length, const char* message, const void* userParam)
	{
		// ignore non-significant error/warning codes
		if (id == 131169 || id == 131185 || id == 131218 || id == 131204) return;

		std::string output;

		output += "OpenGL Debug Message:\n";
		output += "Debug message (" + std::to_string(id) + "): " + message + "\n";

		switch (source)
		{
		case GL_DEBUG_SOURCE_API:				output += "Source: API";				break;
		case GL_DEBUG_SOURCE_WINDOW_SYSTEM:		output += "Source: Window System";		break;
		case GL_DEBUG_SOURCE_SHADER_COMPILER:	output += "Source: Shader Compiler";	break;
		case GL_DEBUG_SOURCE_THIRD_PARTY:		output += "Source: Third Party";		break;
		case GL_DEBUG_SOURCE_APPLICATION:		output += "Source: Application";		break;
		case GL_DEBUG_SOURCE_OTHER:				output += "Source: Other";				break;
		}

		output += "\n";

		switch (type)
		{
		case GL_DEBUG_TYPE_ERROR:               output += "Type: Error";				break;
		case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: output += "Type: Deprecated Behaviour"; break;
		case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  output += "Type: Undefined Behaviour";	break;
		case GL_DEBUG_TYPE_PORTABILITY:         output += "Type: Portability";			break;
		case GL_DEBUG_TYPE_PERFORMANCE:         output += "Type: Performance";			break;
		case GL_DEBUG_TYPE_MARKER:              output += "Type: Marker";				break;
		case GL_DEBUG_TYPE_PUSH_GROUP:          output += "Type: Push Group";			break;
		case GL_DEBUG_TYPE_POP_GROUP:           output += "Type: Pop Group";			break;
		case GL_DEBUG_TYPE_OTHER:               output += "Type: Other";				break;
		}

		output += "\n";

		switch (severity)
		{
		case GL_DEBUG_SEVERITY_HIGH:			output += "Severity: High";				break;
		case GL_DEBUG_SEVERITY_MEDIUM:			output += "Severity: Medium";			break;
		case GL_DEBUG_SEVERITY_LOW:				output += "Severity: Low";				break;
		case GL_DEBUG_SEVERITY_NOTIFICATION:	output += "Severity: Notification";		break;
		}

		switch (severity)
		{
		case GL_DEBUG_SEVERITY_HIGH:			ORHI_LOG_ERROR(output);	break;
		case GL_DEBUG_SEVERITY_MEDIUM:			ORHI_LOG_WARNING(output);	break;
		case GL_DEBUG_SEVERITY_LOW:				ORHI_LOG_INFO(output);		break;
		case GL_DEBUG_SEVERITY_NOTIFICATION:	ORHI_LOG_INFO(output);		break;
		}
	}

	bool GetBool(uint32_t p_parameter)
	{
		GLboolean result;
		glGetBooleanv(p_parameter, &result);
		return static_cast<bool>(result);
	}

	bool GetBool(uint32_t p_parameter, uint32_t p_index)
	{
		GLboolean result;
		glGetBooleani_v(p_parameter, p_index, &result);
		return static_cast<bool>(result);
	}

	int GetInt(uint32_t p_parameter)
	{
		GLint result;
		glGetIntegerv(p_parameter, &result);
		return static_cast<int>(result);
	}

	int GetInt(uint32_t p_parameter, uint32_t p_index)
	{
		GLint result;
		glGetIntegeri_v(p_parameter, p_index, &result);
		return static_cast<int>(result);
	}

	float GetFloat(uint32_t p_parameter)
	{
		GLfloat result;
		glGetFloatv(p_parameter, &result);
		return static_cast<float>(result);
	}

	float GetFloat(uint32_t p_parameter, uint32_t p_index)
	{
		GLfloat result;
		glGetFloati_v(p_parameter, p_index, &result);
		return static_cast<float>(result);
	}

	double GetDouble(uint32_t p_parameter)
	{
		GLdouble result;
		glGetDoublev(p_parameter, &result);
		return static_cast<double>(result);
	}

	double GetDouble(uint32_t p_parameter, uint32_t p_index)
	{
		GLdouble result;
		glGetDoublei_v(p_parameter, p_index, &result);
		return static_cast<double>(result);
	}

	int64_t GetInt64(uint32_t p_parameter)
	{
		GLint64 result;
		glGetInteger64v(p_parameter, &result);
		return static_cast<int64_t>(result);
	}

	int64_t GetInt64(uint32_t p_parameter, uint32_t p_index)
	{
		GLint64 result;
		glGetInteger64i_v(p_parameter, p_index, &result);
		return static_cast<int64_t>(result);
	}

	std::string GetString(uint32_t p_parameter)
	{
		const GLubyte* result = glGetString(p_parameter);
		return result ? reinterpret_cast<const char*>(result) : std::string();
	}

	std::string GetString(uint32_t p_parameter, uint32_t p_index)
	{
		const GLubyte* result = glGetStringi(p_parameter, p_index);
		return result ? reinterpret_cast<const char*>(result) : std::string();
	}

	/**
	* Very expensive! Call it once, and make sure you always keep track of state changes
	*/
	orhi::data::PipelineState RetrieveOpenGLPipelineState()
	{
		using namespace orhi::types;
		using namespace orhi::impl;

		orhi::data::PipelineState pso;

		// Rasterization
		pso.rasterizationMode = static_cast<ERasterizationMode>(GetInt(GL_POLYGON_MODE));
		pso.lineWidthPow2 = orhi::math::conversions::FloatToPow2(GetFloat(GL_LINE_WIDTH));

		// Color write mask
		GLboolean colorWriteMask[4];
		glGetBooleanv(GL_COLOR_WRITEMASK, colorWriteMask);
		pso.colorWriting.r = colorWriteMask[0];
		pso.colorWriting.g = colorWriteMask[1];
		pso.colorWriting.b = colorWriteMask[2];
		pso.colorWriting.a = colorWriteMask[3];

		// Capability
		pso.depthWriting = GetBool(GL_DEPTH_WRITEMASK);
		pso.blending = GetBool(GL_BLEND);
		pso.culling = GetBool(GL_CULL_FACE);
		pso.dither = GetBool(GL_DITHER);
		pso.polygonOffsetFill = GetBool(GL_POLYGON_OFFSET_FILL);
		pso.sampleAlphaToCoverage = GetBool(GL_SAMPLE_ALPHA_TO_COVERAGE);
		pso.depthTest = GetBool(GL_DEPTH_TEST);
		pso.scissorTest = GetBool(GL_SCISSOR_TEST);
		pso.stencilTest = GetBool(GL_STENCIL_TEST);
		pso.multisample = GetBool(GL_MULTISAMPLE);

		// Stencil
		pso.stencilFuncOp = details::ValueToEnum<EComparaisonAlgorithm>(static_cast<GLenum>(GetInt(GL_STENCIL_FUNC)));
		pso.stencilFuncRef = GetInt(GL_STENCIL_REF);
		pso.stencilFuncMask = static_cast<uint32_t>(GetInt(GL_STENCIL_VALUE_MASK));

		pso.stencilWriteMask = static_cast<uint32_t>(GetInt(GL_STENCIL_WRITEMASK));

		pso.stencilOpFail = details::ValueToEnum<EOperation>(static_cast<GLenum>(GetInt(GL_STENCIL_FAIL)));
		pso.depthOpFail = details::ValueToEnum<EOperation>(static_cast<GLenum>(GetInt(GL_STENCIL_PASS_DEPTH_FAIL)));
		pso.bothOpFail = details::ValueToEnum<EOperation>(static_cast<GLenum>(GetInt(GL_STENCIL_PASS_DEPTH_PASS)));

		// Depth
		pso.depthFunc = details::ValueToEnum<EComparaisonAlgorithm>(static_cast<GLenum>(GetInt(GL_DEPTH_FUNC)));

		// Culling
		pso.cullFace = details::ValueToEnum<ECullFace>(static_cast<GLenum>(GetInt(GL_CULL_FACE_MODE)));

		// Blending
		pso.blendingSrcFactor = details::ValueToEnum<EBlendingFactor>(static_cast<GLenum>(GetInt(GL_BLEND_SRC)));
		pso.blendingDestFactor = details::ValueToEnum<EBlendingFactor>(static_cast<GLenum>(GetInt(GL_BLEND_DST)));
		pso.blendingEquation = details::ValueToEnum<EBlendingEquation>(static_cast<GLenum>(GetInt(GL_BLEND_EQUATION)));

		return pso;
	}
}

namespace orhi
{
	template<>
	std::optional<data::PipelineState> Backend::Init(bool debug)
	{
		const int error = gladLoadGL();

		if (error == 0)
		{
			ORHI_LOG_ERROR("GLAD failed to initialize");
			return std::nullopt;
		}

		ORHI_LOG_INFO("OpenGL backend initialized.");

		if (debug)
		{
			glEnable(GL_DEBUG_OUTPUT);
			glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
			glDebugMessageCallback(GLDebugMessageCallback, nullptr);
		}

		// Seamless cubemap (always on)
		glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glCullFace(GL_BACK);

		return RetrieveOpenGLPipelineState();
	}

	template<>
	void Backend::Clear(bool p_colorBuffer, bool p_depthBuffer, bool p_stencilBuffer)
	{
		GLbitfield clearMask = 0;
		if (p_colorBuffer) clearMask |= GL_COLOR_BUFFER_BIT;
		if (p_depthBuffer) clearMask |= GL_DEPTH_BUFFER_BIT;
		if (p_stencilBuffer) clearMask |= GL_STENCIL_BUFFER_BIT;

		if (clearMask != 0)
		{
			glClear(clearMask);
		}
	}

	template<>
	void Backend::DrawElements(types::EPrimitiveMode p_primitiveMode, uint32_t p_indexCount)
	{
		glDrawElements(details::EnumToValue<GLenum>(p_primitiveMode), p_indexCount, GL_UNSIGNED_INT, nullptr);
	}

	template<>
	void Backend::DrawElementsInstanced(types::EPrimitiveMode p_primitiveMode, uint32_t p_indexCount, uint32_t p_instances)
	{
		glDrawElementsInstanced(details::EnumToValue<GLenum>(p_primitiveMode), p_indexCount, GL_UNSIGNED_INT, nullptr, p_instances);
	}

	template<>
	void Backend::DrawArrays(types::EPrimitiveMode p_primitiveMode, uint32_t p_vertexCount)
	{
		glDrawArrays(details::EnumToValue<GLenum>(p_primitiveMode), 0, p_vertexCount);
	}

	template<>
	void Backend::DrawArraysInstanced(types::EPrimitiveMode p_primitiveMode, uint32_t p_vertexCount, uint32_t p_instances)
	{
		glDrawArraysInstanced(details::EnumToValue<GLenum>(p_primitiveMode), 0, p_vertexCount, p_instances);
	}

	template<>
	void Backend::SetClearColor(float p_red, float p_green, float p_blue, float p_alpha)
	{
		glClearColor(p_red, p_green, p_blue, p_alpha);
	}

	template<>
	void Backend::SetRasterizationLinesWidth(float p_width)
	{
		glLineWidth(p_width);
	}

	template<>
	void Backend::SetRasterizationMode(types::ERasterizationMode p_rasterizationMode)
	{
		glPolygonMode(GL_FRONT_AND_BACK, details::EnumToValue<GLenum>(p_rasterizationMode));
	}

	template<>
	void Backend::SetCapability(types::ERenderingCapability p_capability, bool p_value)
	{
		(p_value ? glEnable : glDisable)(details::EnumToValue<GLenum>(p_capability));
	}

	template<>
	bool Backend::GetCapability(types::ERenderingCapability p_capability)
	{
		return glIsEnabled(details::EnumToValue<GLenum>(p_capability));
	}

	template<>
	void Backend::SetStencilAlgorithm(types::EComparaisonAlgorithm p_algorithm, int32_t p_reference, uint32_t p_mask)
	{
		glStencilFunc(details::EnumToValue<GLenum>(p_algorithm), p_reference, p_mask);
	}

	template<>
	void Backend::SetDepthAlgorithm(types::EComparaisonAlgorithm p_algorithm)
	{
		glDepthFunc(details::EnumToValue<GLenum>(p_algorithm));
	}

	template<>
	void Backend::SetStencilMask(uint32_t p_mask)
	{
		glStencilMask(p_mask);
	}

	template<>
	void Backend::SetStencilOperations(types::EOperation p_stencilFail, types::EOperation p_depthFail, types::EOperation p_bothPass)
	{
		glStencilOp(
			details::EnumToValue<GLenum>(p_stencilFail),
			details::EnumToValue<GLenum>(p_depthFail),
			details::EnumToValue<GLenum>(p_bothPass)
		);
	}

	template<>
	void Backend::SetBlendingFunction(types::EBlendingFactor p_sourceFactor, types::EBlendingFactor p_destinationFactor)
	{
		glBlendFunc(
			details::EnumToValue<GLenum>(p_sourceFactor),
			details::EnumToValue<GLenum>(p_destinationFactor)
		);
	}

	template<>
	void Backend::SetBlendingEquation(types::EBlendingEquation p_equation)
	{
		glBlendEquation(details::EnumToValue<GLenum>(p_equation));
	}

	template<>
	void Backend::SetCullFace(types::ECullFace p_cullFace)
	{
		glCullFace(details::EnumToValue<GLenum>(p_cullFace));
	}

	template<>
	void Backend::SetDepthWriting(bool p_enable)
	{
		glDepthMask(p_enable);
	}

	template<>
	void Backend::SetColorWriting(bool p_enableRed, bool p_enableGreen, bool p_enableBlue, bool p_enableAlpha)
	{
		glColorMask(p_enableRed, p_enableGreen, p_enableBlue, p_enableAlpha);
	}

	template<>
	void Backend::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
	{
		glViewport(x, y, width, height);
	}

	template<>
	std::string Backend::GetVendor()
	{
		return GetString(GL_VENDOR);
	}

	template<>
	std::string Backend::GetHardware()
	{
		return GetString(GL_RENDERER);
	}

	template<>
	std::string Backend::GetVersion()
	{
		return GetString(GL_VERSION);
	}

	template<>
	std::string Backend::GetShadingLanguageVersion()
	{
		return GetString(GL_SHADING_LANGUAGE_VERSION);
	}
}

#endif // #if defined(ORHI_COMPILE_OPENGL)
