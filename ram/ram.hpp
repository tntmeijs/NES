#ifndef NES_RAM_HPP
#define NES_RAM_HPP

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

	public:
		/**
		 * Create a new RAM object
		 */
		RAM();

		/**
		 * Initialize the RAM by allocating the specified number of bytes
		 */
		void Initialize(std::uint32_t size);

		/**
		 * Deallocates the block of memory
		 */
		void Delete();

		/**
		 * Read a byte from memory
		 * @param	address		Address pointing to the byte to read
		 * @return	Value of the byte at the specified memory address
		 */
		const std::uint8_t ReadByte(std::uint16_t address) const;

		/**
		 * Set the value of a byte in memory
		 * @param	address		Address pointing to the byte to read
		 * @param	value		Value to set the byte to
		 */
		void WriteByte(std::uint16_t address, std::uint8_t value);

		/**
		 * Retrieve a pointer to the block of memory that backs the RAM object
		 * @return	Pointer to the raw memory block
		 */
		std::uint8_t* const GetRaw() const;

		/**
		 * Store a ROM into memory
		 * @param	romFile		ROM data to store
		 */
		void StoreRomData(const RomFile& romFile);

	public:
		/** Size of the RAM in bytes */
		std::uint32_t Size;

	private:
		std::uint8_t* Memory;
	};
}

#endif //! NES_RAM_HPP
