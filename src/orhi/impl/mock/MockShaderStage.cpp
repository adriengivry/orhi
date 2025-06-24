/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#if defined(ORHI_COMPILE_MOCK)

#include <orhi/impl/mock/ShaderStage.h>

using namespace orhi::impl::mock;

namespace orhi
{
	template<>
	ShaderStage::TShaderStage(types::EShaderType p_type) : m_context{
		.type = p_type,
	}
	{
	}

	template<>
	ShaderStage::~TShaderStage()
	{
	}

	template<>
	void ShaderStage::Upload(const std::string& p_source) const
	{
	}

	template<>
	orhi::data::ShaderCompilationResult ShaderStage::Compile() const
	{
		return {
			.success = true
		};
	}

	template<>
	uint32_t ShaderStage::GetID() const
	{
		return 0;
	}

	template<>
	types::EShaderType ShaderStage::GetType() const
	{
		return m_context.type;
	}
}

#endif // #if defined(ORHI_COMPILE_MOCK)
