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
			std::uint8_t bit0 : 1;
			std::uint8_t bit1 : 1;
			std::uint8_t bit2 : 1;
			std::uint8_t bit3 : 1;
			std::uint8_t bit4 : 1;
			std::uint8_t bit5 : 1;
			std::uint8_t bit6 : 1;
			std::uint8_t bit7 : 1;
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
	inline constexpr bool IsNthBitSet(Byte byte, std::uint8_t n)
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

	/**
	 * Set a bit when the input bit is set, clear a bit when the input bit is
	 * clear. This is useful when matching bits at specific indices.
	 * @param   target  Byte whose bits will be updated
	 * @param   source  Byte whose bits will be compared against
	 * @param   n       Bit index to compare
	 */
	inline constexpr void MatchBitStateOfNthBit(std::uint8_t& target, std::uint8_t source, std::uint8_t n)
	{
		SetNthBitState(target, n, IsNthBitSet(source, n));
	}

	/**
	 * Set a bit when the input bit is set, clear a bit when the input bit is
	 * clear. This is useful when matching bits at specific indices.
	 * @param   target  Byte whose bits will be updated
	 * @param   source  Byte whose bits will be compared against
	 * @param   n       Bit index to compare
	 */
	inline constexpr void MatchBitStateOfNthBit(Byte& target, Byte source, std::uint8_t n)
	{
		SetNthBitState(target, n, IsNthBitSet(source, n));
	}

	/**
	 * Combine two bytes into a 16-bit address
	 * @param	msb		Most significant byte
	 * @param	lsb		Least significant byte
	 * @return	Address that consists out of the two bytes
	 */
	inline constexpr std::uint16_t ConstructAddressFromBytes(std::uint8_t msb, std::uint8_t lsb)
	{
		return ((msb << 8) | lsb);
	}

	/**
	 * Combine two bytes into a 16-bit address
	 * @param	msb		Most significant byte
	 * @param	lsb		Least significant byte
	 * @return	Address that consists out of the two bytes
	 */
	inline constexpr std::uint16_t ConstructAddressFromBytes(Byte msb, Byte lsb)
	{
		return ((msb.value << 8) | lsb.value);
	}
}

#endif //! NES_BIT_TOOLS_HPP
