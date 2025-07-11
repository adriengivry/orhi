/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <cstdint>

namespace orhi::math::conversions
{
	/**
	* @brief Computes the base-2 logarithm of a floating-point number at compile time
	* @param n The input value to compute log2 for
	* @return The base-2 logarithm of n as an unsigned integer
	*/
	constexpr uint32_t _log2(float n)
	{
		return ((n < 2) ? 1 : 1 + _log2(n / 2));
	}

	/**
	* @brief Converts a power-of-two exponent to its corresponding floating-point value
	* @param p_value The exponent value (must be valid for bit shifting)
	* @return The floating-point result of 2^p_value
	*/
	constexpr float Pow2toFloat(uint8_t p_value)
	{
		return static_cast<float>(1U << p_value);
	}

	/**
	* @brief Converts a floating-point power-of-two value to its exponent
	* @param p_value The power-of-two value to convert
	* @return The exponent as an unsigned 8-bit integer
	*/
	constexpr uint8_t FloatToPow2(float p_value)
	{
		return static_cast<uint8_t>(_log2(p_value) - 1);
	}
}
