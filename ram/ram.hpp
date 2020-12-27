#ifndef NES_RAM_HPP
#define NES_RAM_HPP

#include "utility/bit_tools.hpp"

#include <array>
#include <cstdint>

namespace nes
{
	class RomFile;

	class RAM
	{
	public:
		/** Starting address of the first ROM bank */
		const std::uint16_t FIRST_ROM_BANK_ADDRESS;

		/** Starting address of the second ROM bank */
		const std::uint16_t SECOND_ROM_BANK_ADDRESS;

		/** Stack starts at this address */
		const std::uint16_t STACK_START_ADDRESS;

	public:
		/**
		 * Create a new RAM object
		 */
		RAM();

		/**
		 * Read a byte from memory
		 * @param	address		Address pointing to the byte to read
		 * @return	Value of the byte at the specified memory address
		 */
		Byte ReadByte(std::uint16_t address) const;

		/**
		 * Set the value of a byte in memory
		 * @param	address		Address pointing to the byte to read
		 * @param	value		Value to set the byte to
		 */
		void WriteByte(std::uint16_t address, Byte value);

		/**
		 * Store a ROM into memory
		 * @param	romFile		ROM data to store
		 */
		void StoreRomData(const RomFile& romFile);

		/**
		 * Returns the size of the RAM in bytes
		 * @return	Size of the RAM in bytes
		 */
		std::size_t GetSize() const;

	private:
		std::array<Byte, 0x10000> Memory;
	};
}

#endif //! NES_RAM_HPP
