#ifndef NES_INES_HPP
#define NES_INES_HPP

#include <cstdint>
#include <string_view>
#include <vector>

namespace nes
{
	/**
	 * NES file format implementation
	 */
	class INES
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

	private:
		std::vector<std::uint8_t> RawData;
	};
}

#endif //! NES_INES_HPP
