#ifndef NES_BIT_TOOLS_HPP
#define NES_BIT_TOOLS_HPP

#include <cstdint>

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
}

#endif //! NES_BIT_TOOLS_HPP
