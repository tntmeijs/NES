#ifndef NES_ROM_FILE_HPP
#define NES_ROM_FILE_HPP

#include <cstdint>
#include <string_view>
#include <vector>

namespace nes
{
	class RomFile
	{
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

	private:
		std::vector<std::uint8_t> RawData;
	};
}

#endif //! NES_ROM_FILE_HPP
