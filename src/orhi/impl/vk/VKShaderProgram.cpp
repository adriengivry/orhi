/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#if defined(ORHI_COMPILE_VULKAN)

#include <orhi/impl/vk/ShaderProgram.h>
#include <orhi/impl/vk/Texture.h>

using namespace orhi::impl::vk;

namespace
{
	std::unordered_map<std::string, orhi::data::UniformInfo> emptyUniforms;
}

namespace orhi
{
	template<>
	ShaderProgram::TShaderProgram()
	{
	}

	template<>
	ShaderProgram::~TShaderProgram()
	{
	}

	template<>
	void ShaderProgram::Bind() const
	{
	}

	template<>
	void ShaderProgram::Unbind() const
	{
	}

	template<>
	uint32_t ShaderProgram::GetID() const
	{
		return 0;
	}

	template<>
	void ShaderProgram::Attach(const ShaderStage& p_shader)
	{
	}

	template<>
	void ShaderProgram::Detach(const ShaderStage& p_shader)
	{

	}

	template<>
	void ShaderProgram::DetachAll()
	{
	}

	template<>
	orhi::data::ShaderLinkingResult ShaderProgram::Link()
	{
		return {
			.success = true
		};
	}

#define DECLARE_SET_UNIFORM_FUNCTION(type) \
template<> \
template<> \
void ShaderProgram::SetUniform<type>(const std::string&, const type&) \
{ \
}

#define DECLARE_GET_UNIFORM_FUNCTION(type) \
template<> \
template<> \
type ShaderProgram::GetUniform<type>(const std::string&) \
{ \
	return type{}; \
}

	DECLARE_SET_UNIFORM_FUNCTION(int);
	DECLARE_SET_UNIFORM_FUNCTION(float);
	DECLARE_SET_UNIFORM_FUNCTION(math::Vec2);
	DECLARE_SET_UNIFORM_FUNCTION(math::Vec3);
	DECLARE_SET_UNIFORM_FUNCTION(math::Vec4);
	DECLARE_SET_UNIFORM_FUNCTION(math::Mat4);

	DECLARE_GET_UNIFORM_FUNCTION(int);
	DECLARE_GET_UNIFORM_FUNCTION(float);
	DECLARE_GET_UNIFORM_FUNCTION(math::Vec2);
	DECLARE_GET_UNIFORM_FUNCTION(math::Vec3);
	DECLARE_GET_UNIFORM_FUNCTION(math::Vec4);
	DECLARE_GET_UNIFORM_FUNCTION(math::Mat4);

	template<>
	void ShaderProgram::QueryUniforms()
	{
	}

	template<>
	std::optional<std::reference_wrapper<const orhi::data::UniformInfo>> ShaderProgram::GetUniformInfo(const std::string& p_name) const
	{
		return std::nullopt;
	}

	template<>
	const std::unordered_map<std::string, orhi::data::UniformInfo>& ShaderProgram::GetUniforms() const
	{
		return emptyUniforms;
	}
}

#endif // #if defined(ORHI_COMPILE_VULKAN)
