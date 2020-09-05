#ifndef NES_ROM_FILE_HPP
#define NES_ROM_FILE_HPP

#include "utility/literals.hpp"

#include <cstdint>
#include <string_view>
#include <vector>

namespace nes
{
	class RomFile
	{
	public:
		/**
		 * Nametable mirroring types
		 */
		enum class MirroringType
		{
			Vertical,
			Horizontal
		};

		/** Size of a single ROM bank in bytes */
		static constexpr std::uint16_t ROM_BANK_SIZE = 16_KB;

		/** Size of a trainer in bytes */
		static constexpr std::uint16_t ROM_TRAINER_SIZE = 512;

	public:
		/**
		 * Read a NES file from disk
		 * @param	path	Path to the NES file
		 * @return	True when the loading succeeded, false otherwise
		 */
		bool LoadFromDisk(std::string_view path);

		/**
		 * Check if the magic number is present in the file header
		 * @return	True when the ROM is a valid NES ROM, false otherwise
		 */
		bool IsValidRom() const;

		/**
		 * Get the raw ROM data
		 * @return	Bytes that make up the entire ROM
		 */
		const std::vector<std::uint8_t>& GetRaw() const;

		/**
		 * Get the number of ROM banks
		 * @return	Number of ROM banks
		 */
		std::uint8_t GetNumberOfRomBanks() const;

		/**
		 * Get the number of VROM banks
		 * @return	Number of VROM banks
		 */
		std::uint8_t GetNumberOfVRomBanks() const;

		/**
		 * Get the number of RAM banks
		 * For compatibility with old .nes files, assume 1x8kB RAM page when this
		 * return value equals zero
		 * @return	Number of RAM banks
		 */
		std::uint8_t GetNumberOfRamBanks() const;

		/**
		 * Retrieve the ROM mapper type ID
		 * @return	ROM mapper type ID
		 */
		std::uint8_t GetRomMapperTypeId() const;

		/**
		 * Get the nametable mirroring type
		 * @return	Mirroring type
		 */
		MirroringType GetNametableMirroringType() const;

		/**
		 * Check if this ROM expects battery-backed PRG RAM at 0x6000 - 0x7FFF
		 * @return	True when the ROM expects battery-backed PRG RAM, false when it does not
		 */
		bool HasBatteryBackedPRGRam() const;

		/**
		 * Check if this ROM has a trainer at 0x7000 - 0x71FF
		 * @return	True when the ROM contains a trainer, false when it does not
		 */
		bool HasTrainer() const;

		/**
		 * Ignore mirroring control or mirroring bit, instead, provide four-screen VRAM
		 * @return	True when the ROM expects four-screen VRAM mode
		 */
		bool UseFourScreenVRam() const;

		/**
		 * Check if this ROM is from a VS-system cartridge
		 * @return	True when the ROM is from a VS-system cartridge, false when it is not
		 */
		bool IsVsSystem() const;

		/**
		 * Check if this is a PAL cartridge
		 * @return	True when the ROM is from a PAL cartridge, otherwise assume NTSC
		 */
		bool IsPal() const;

		/**
		 * Get the index of the first ROM bank byte
		 * @return	Start index of the first ROM bank
		 */
		std::uint16_t GetFirstRomBankByteIndex() const;

		/**
		 * Get the index of the second ROM bank byte
		 * @return	Start index of the second ROM bank
		 */
		std::uint16_t GetSecondRomBankByteIndex() const;

	private:
		std::vector<std::uint8_t> RawData;
	};
}

#endif //! NES_ROM_FILE_HPP
