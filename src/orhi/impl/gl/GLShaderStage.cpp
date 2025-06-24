/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#if defined(ORHI_COMPILE_OPENGL)

#include <algorithm>

#include <orhi/debug/Log.h>
#include <orhi/impl/gl/details/glad/glad.h>
#include <orhi/impl/gl/details/Types.h>
#include <orhi/impl/gl/ShaderStage.h>

using namespace orhi::impl::gl;

namespace orhi
{
	template<>
	ShaderStage::TShaderStage(types::EShaderType p_type) : m_context{
		.id = static_cast<uint32_t>(glCreateShader(utils::EnumToValue<GLenum>(p_type))),
		.type = p_type,
	}
	{
	}

	template<>
	ShaderStage::~TShaderStage()
	{
		glDeleteShader(m_context.id);
	}

	template<>
	void ShaderStage::Upload(const std::string& p_source) const
	{
		const char* source = p_source.c_str();
		glShaderSource(m_context.id, 1, &source, nullptr);
	}

	template<>
	orhi::data::ShaderCompilationResult ShaderStage::Compile() const
	{
		glCompileShader(m_context.id);

		GLint compileStatus;
		glGetShaderiv(m_context.id, GL_COMPILE_STATUS, &compileStatus);

		if (compileStatus == GL_FALSE)
		{
			GLint maxLength;
			glGetShaderiv(m_context.id, GL_INFO_LOG_LENGTH, &maxLength);

			std::string errorLog(maxLength, ' ');
			glGetShaderInfoLog(m_context.id, maxLength, &maxLength, errorLog.data());

			return {
				.success = false,
				.message = errorLog
			};
		}

		return {
			.success = true
		};
	}

	template<>
	uint32_t ShaderStage::GetID() const
	{
		return m_context.id;
	}

	template<>
	types::EShaderType ShaderStage::GetType() const
	{
		return m_context.type;
	}
}

#endif // #if defined(ORHI_COMPILE_OPENGL)
