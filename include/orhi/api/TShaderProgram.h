/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <optional>
#include <unordered_map>

#include <orhi/math/Mat3.h>
#include <orhi/math/Mat4.h>
#include <orhi/math/Vec2.h>
#include <orhi/math/Vec3.h>
#include <orhi/math/Vec4.h>

#include <orhi/api/TShaderStage.h>
#include <orhi/types/EGraphicsBackend.h>
#include <orhi/data/UniformInfo.h>
#include <orhi/data/ShaderLinkingResult.h>

namespace orhi::api
{
	template<typename T>
	concept SupportedUniformType =
		std::same_as<T, float> ||
		std::same_as<T, int> ||
		std::same_as<T, math::Vec2> ||
		std::same_as<T, math::Vec3> ||
		std::same_as<T, math::Vec4> ||
		std::same_as<T, math::Mat3> ||
		std::same_as<T, math::Mat4>;

	/**
	* Represents a shader program, used to link shader stages together.
	*/
	template<types::EGraphicsBackend Backend, class ProgramContext, class StageContext>
	class TShaderProgram final
	{
	public:
		/**
		* Creates a shader program.
		*/
		TShaderProgram();

		/**
		* Destroys a shader program.
		*/
		~TShaderProgram();

		/**
		* Attaches a shader stage to the program.
		* @param p_shader
		*/
		void Attach(const TShaderStage<Backend, StageContext>& p_shader);

		/**
		* Detaches a shader stage to the program.
		* @param p_shader
		*/
		void Detach(const TShaderStage<Backend, StageContext>& p_shader);

		/**
		* Detaches all shader stages from the program.
		*/
		void DetachAll();

		/**
		* Links the shader stages together.
		* @return The linking result
		*/
		orhi::data::ShaderLinkingResult Link();

		/**
		* Binds the program.
		*/
		void Bind() const;

		/**
		* Unbinds the program.
		*/
		void Unbind() const;

		/**
		* Returns the ID of the program.
		*/
		uint32_t GetID() const;

		/**
		* Sends a uniform value associated with the given name to the GPU.
		* @param p_name
		* @param p_value
		*/
		template<SupportedUniformType T>
		void SetUniform(const std::string& p_name, const T& p_value);

		/**
		* Returns the value of a uniform associated with the given name.
		* @param p_name
		* @param p_value
		*/
		template<SupportedUniformType T>
		T GetUniform(const std::string& p_name);

		/**
		* Returns information about the uniform identified by the given name or std::nullopt if not found.
		* @param p_name
		*/
		std::optional<std::reference_wrapper<const data::UniformInfo>> GetUniformInfo(const std::string& p_name) const;

		/**
		* Queries the uniforms from the program and caches them in memory.
		*/
		void QueryUniforms();

		/**
		* Returns the uniforms associated with this program.
		*/
		const std::unordered_map<std::string, data::UniformInfo>& GetUniforms() const;

	private:
		ProgramContext m_context;
	};
}
