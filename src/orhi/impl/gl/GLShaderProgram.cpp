/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#if defined(ORHI_COMPILE_OPENGL)

#include <array>

#include <orhi/debug/Assert.h>
#include <orhi/debug/Log.h>
#include <orhi/impl/gl/details/glad/glad.h>
#include <orhi/impl/gl/details/Types.h>
#include <orhi/impl/gl/ShaderProgram.h>
#include <orhi/impl/gl/Texture.h>
#include <orhi/Texture.h>

using namespace orhi::impl::gl;

namespace
{
	constexpr bool IsReservedUniform(std::string_view p_name)
	{
		return p_name.starts_with("ubo_") || p_name.starts_with("ReflectionUBO");
	}
}

namespace orhi
{
	template<>
	ShaderProgram::TShaderProgram() : m_context{ .id = glCreateProgram() }
	{

	}

	template<>
	ShaderProgram::~TShaderProgram()
	{
		glDeleteProgram(m_context.id);
	}

	template<>
	void ShaderProgram::Bind() const
	{
		glUseProgram(m_context.id);
	}

	template<>
	void ShaderProgram::Unbind() const
	{
		glUseProgram(0);
	}

	template<>
	uint32_t ShaderProgram::GetID() const
	{
		return m_context.id;
	}

	template<>
	void ShaderProgram::Attach(const ShaderStage& p_shader)
	{
		glAttachShader(m_context.id, p_shader.GetID());
		m_context.attachedShaders.push_back(std::ref(p_shader));
	}

	template<>
	void ShaderProgram::Detach(const ShaderStage& p_shader)
	{
		glDetachShader(m_context.id, p_shader.GetID());
		m_context.attachedShaders.erase(std::remove_if(
			m_context.attachedShaders.begin(),
			m_context.attachedShaders.end(),
			[&p_shader](const std::reference_wrapper<const ShaderStage> shader) {
				return shader.get().GetID() == p_shader.GetID();
			}
		));
	}

	template<>
	void ShaderProgram::DetachAll()
	{
		for (auto& shader : m_context.attachedShaders)
		{
			glDetachShader(m_context.id, shader.get().GetID());
		}

		m_context.attachedShaders.clear();
	}

	template<>
	orhi::data::ShaderLinkingResult ShaderProgram::Link()
	{
		glLinkProgram(m_context.id);

		GLint linkStatus;
		glGetProgramiv(m_context.id, GL_LINK_STATUS, &linkStatus);

		if (linkStatus == GL_FALSE)
		{
			GLint maxLength;
			glGetProgramiv(m_context.id, GL_INFO_LOG_LENGTH, &maxLength);

			std::string errorLog(maxLength, ' ');
			glGetProgramInfoLog(m_context.id, maxLength, &maxLength, errorLog.data());

			return {
				.success = false,
				.message = errorLog
			};
		}

		QueryUniforms();

		return {
			.success = true
		};
	}

#define DECLARE_GET_UNIFORM_FUNCTION(type, glType, func) \
template<> \
template<> \
type ShaderProgram::GetUniform<type>(const std::string& p_name) \
{ \
	type result{}; \
	if (m_context.uniformsLocationCache.contains(p_name)) \
	{ \
		if (const uint32_t location = m_context.uniformsLocationCache.at(p_name)) \
		{ \
			func(m_context.id, location, reinterpret_cast<glType*>(&result)); \
		} \
	} \
	return result; \
}

	DECLARE_GET_UNIFORM_FUNCTION(int, GLint, glGetUniformiv);
	DECLARE_GET_UNIFORM_FUNCTION(float, GLfloat, glGetUniformfv);
	DECLARE_GET_UNIFORM_FUNCTION(math::Vec2, GLfloat, glGetUniformfv);
	DECLARE_GET_UNIFORM_FUNCTION(math::Vec3, GLfloat, glGetUniformfv);
	DECLARE_GET_UNIFORM_FUNCTION(math::Vec4, GLfloat, glGetUniformfv);
	DECLARE_GET_UNIFORM_FUNCTION(math::Mat3, GLfloat, glGetUniformfv);
	DECLARE_GET_UNIFORM_FUNCTION(math::Mat4, GLfloat, glGetUniformfv);

#define DECLARE_SET_UNIFORM_FUNCTION(type, func, ...) \
template<> \
template<> \
void ShaderProgram::SetUniform<type>(const std::string& p_name, const type& value) \
{ \
	if (m_context.uniformsLocationCache.contains(p_name)) \
	{ \
		func(m_context.uniformsLocationCache.at(p_name), __VA_ARGS__); \
	} \
}

	DECLARE_SET_UNIFORM_FUNCTION(int, glUniform1i, value);
	DECLARE_SET_UNIFORM_FUNCTION(float, glUniform1f, value);
	DECLARE_SET_UNIFORM_FUNCTION(math::Vec2, glUniform2f, value.x, value.y);
	DECLARE_SET_UNIFORM_FUNCTION(math::Vec3, glUniform3f, value.x, value.y, value.z);
	DECLARE_SET_UNIFORM_FUNCTION(math::Vec4, glUniform4f, value.x, value.y, value.z, value.w);
	DECLARE_SET_UNIFORM_FUNCTION(math::Mat3, glUniformMatrix3fv, 1, GL_FALSE, &value[0][0]);
	DECLARE_SET_UNIFORM_FUNCTION(math::Mat4, glUniformMatrix4fv, 1, GL_FALSE, &value[0][0]);

	template<>
	void ShaderProgram::QueryUniforms()
	{
		m_context.uniforms.clear();

		std::array<GLchar, 256> nameBuffer;

		GLint activeUniformCount = 0;
		glGetProgramiv(m_context.id, GL_ACTIVE_UNIFORMS, &activeUniformCount);

		for (GLint i = 0; i < activeUniformCount; ++i)
		{
			GLint arraySize = 0;
			GLenum type = 0;
			GLsizei actualLength = 0;

			glGetActiveUniform(m_context.id, i, static_cast<GLsizei>(nameBuffer.size()), &actualLength, &arraySize, &type, nameBuffer.data());

			const auto name = std::string{ nameBuffer.data(), static_cast<size_t>(actualLength) };
			const auto uniformType = details::ValueToEnum<types::EUniformType>(type);

			// Skip reserved uniforms (e.g. ubo uniforms)
			if (IsReservedUniform(name))
			{
				continue;
			}

			const auto location = glGetUniformLocation(m_context.id, name.c_str());
			ORHI_ASSERT(location != -1, "Failed to get uniform location for: " + name);
			m_context.uniformsLocationCache.emplace(name, static_cast<uint32_t>(location));

			const std::any uniformValue = [&]() -> std::any {
				switch (uniformType)
				{
					using enum types::EUniformType;
				case BOOL: return static_cast<bool>(GetUniform<int>(name));
				case INT: return GetUniform<int>(name);
				case FLOAT: return GetUniform<float>(name);
				case FLOAT_VEC2: return GetUniform<math::Vec2>(name);
				case FLOAT_VEC3: return GetUniform<math::Vec3>(name);
				case FLOAT_VEC4: return GetUniform<math::Vec4>(name);
				case FLOAT_MAT3: return GetUniform<math::Mat3>(name);
				case FLOAT_MAT4: return GetUniform<math::Mat4>(name);
				case SAMPLER_2D: return std::make_any<Texture*>(nullptr);
				case SAMPLER_CUBE: return std::make_any<Texture*>(nullptr);
				default: return std::nullopt;
				}
				}();

			// Only add the uniform if it has a value (unsupported uniform types will be ignored)
			if (uniformValue.has_value())
			{
				m_context.uniforms.emplace(name, data::UniformInfo{
					.type = uniformType,
					.name = name,
					.defaultValue = uniformValue
					});
			}
		}
	}

	template<>
	std::optional<std::reference_wrapper<const orhi::data::UniformInfo>> ShaderProgram::GetUniformInfo(const std::string& p_name) const
	{
		if (m_context.uniforms.contains(p_name))
		{
			return m_context.uniforms.at(p_name);
		}

		return std::nullopt;
	}

	template<>
	const std::unordered_map<std::string, orhi::data::UniformInfo>& ShaderProgram::GetUniforms() const
	{
		return m_context.uniforms;
	}
}

#endif // #if defined(ORHI_COMPILE_OPENGL)
