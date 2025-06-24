/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/types/EGraphicsBackend.h>
#include <orhi/types/EShaderType.h>
#include <orhi/data/ShaderCompilationResult.h>

namespace orhi::api
{
	/**
	* Represents a part of a shader program that is responsible for a specific stage (vertex, fragment, geometry, etc.).
	*/
	template<types::EGraphicsBackend Backend, class Context>
	class TShaderStage final
	{
	public:
		/**
		* Creates a shader stage of the given type.
		* @param p_type
		*/
		TShaderStage(types::EShaderType p_type);

		/**
		* Destructor of the shader stage.
		*/
		~TShaderStage();

		/**
		* Uploads the shader source to the graphics backend memory.
		* @param p_source
		*/
		void Upload(const std::string& p_source) const;

		/**
		* Compiles the uploaded shader source.
		* @note Use this method after uploading the shader source.
		* @return The compilation result.
		*/
		data::ShaderCompilationResult Compile() const;

		/**
		* Returns the ID of the shader stage.
		*/
		uint32_t GetID() const;

		/**
		* Returns the type of shader stage.
		*/
		types::EShaderType GetType() const;

	private:
		Context m_context;
	};
}
