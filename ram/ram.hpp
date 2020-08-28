#ifndef NES_RAM_HPP
#define NES_RAM_HPP

#include <cstdint>

namespace nes
{
	class RAM
	{
	public:
		/**
		 * Create a new RAM object
		 */
		RAM();

		/**
		 * Initialize the RAM
		 * Allocates 2048 bytes of memory for the emulator to use
		 */
		void Initialize();

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

	public:
		/** Size of the memory block in bytes */
		const std::uint32_t SIZE;

	private:
		std::uint8_t* Memory;
	};
}

#endif //! NES_RAM_HPP
