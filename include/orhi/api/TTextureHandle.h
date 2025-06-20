/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <optional>

#include <orhi/types/EGraphicsBackend.h>
#include <orhi/types/ETextureType.h>

namespace orhi::api
{
	/**
	* Represents a texture handle, acts as a view to the texture.
	*/
	template<types::EGraphicsBackend Backend, class Context>
	class TTextureHandle
	{
	public:
		/**
		* Binds the texture to the given slot.
		* @param p_slot Optional slot to bind the texture to.
		*/
		void Bind(std::optional<uint32_t> p_slot = std::nullopt) const;

		/**
		* Unbinds the texture.
		*/
		void Unbind() const;

		/**
		* Returns the ID associated with the texture.
		* @return The texture ID.
		*/
		uint32_t GetID() const;

		/**
		* Returns the texture type
		*/
		types::ETextureType GetType() const;

	protected:
		TTextureHandle(types::ETextureType p_type);
		TTextureHandle(types::ETextureType p_type, uint32_t p_id);

	protected:
		Context m_context;
	};
}
