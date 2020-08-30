#ifndef NES_INES_HPP
#define NES_INES_HPP

#include <string_view>

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
	};
}

#endif //! NES_INES_HPP
