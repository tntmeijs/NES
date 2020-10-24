#ifndef NES_BIT_TOOLS_HPP
#define NES_BIT_TOOLS_HPP

#include <cstdint>

/**
 * This file contains a collection of utility functions and structures to help
 * simplify working with bits and bytes
 */
namespace nes
{
	/**
	 * Byte type, allows for easy access to its full value or to individual bits
	 */
	union Byte
	{
		struct
		{
			unsigned char bit0 : 1;
			unsigned char bit1 : 1;
			unsigned char bit2 : 1;
			unsigned char bit3 : 1;
			unsigned char bit4 : 1;
			unsigned char bit5 : 1;
			unsigned char bit6 : 1;
			unsigned char bit7 : 1;
		};

		std::uint8_t value;
	};

	/**
	 * Check if bit N has been set
	 * @param   byte    Byte to check
	 * @param   n       Bit to check
	 * @return  True when the flag is set, false when clear
	 */
	inline constexpr bool IsNthBitSet(std::uint8_t byte, std::uint8_t n)
	{
		return ((byte & (1 << n)) != 0);
	}

	/**
	 * Check if bit N has been set
	 * @param   byte    Byte to check
	 * @param   n       Bit to check
	 * @return  True when the flag is set, false when clear
	 */
	inline constexpr bool IsNthBitSet(const Byte& byte, std::uint8_t n)
	{
		return ((byte.value & (1 << n)) != 0);
	}

	/**
	 * Set the Nth bit to 0 or 1
	 * @param   target  Target byte to modify
	 * @param   n       Bit to modify
	 * @param   state   State to set the bit to
	 */
	inline constexpr void SetNthBitState(std::uint8_t& target, std::uint8_t n, bool state)
	{
		if (state)
		{
			target |= (1 << n);
		}
		else
		{
			target &= ~(1 << n);
		}
	}

	/**
	 * Set the Nth bit to 0 or 1
	 * @param   target  Target byte to modify
	 * @param   n       Bit to modify
	 * @param   state   State to set the bit to
	 */
	inline constexpr void SetNthBitState(Byte& target, std::uint8_t n, bool state)
	{
		if (state)
		{
			target.value |= (1 << n);
		}
		else
		{
			target.value &= ~(1 << n);
		}
	}
}

#endif //! NES_BIT_TOOLS_HPP
