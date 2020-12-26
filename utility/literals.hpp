#ifndef NES_UTILITY_LITERALS_HPP
#define NES_UTILITY_LITERALS_HPP

/**
 * Easily convert from bytes to kilobytes
 * @param   size    Number of kilobytes
 * @return  Kilobytes
 */
inline constexpr long operator""_KB(const unsigned long long size)
{
	return size * 1024L;
}

#endif //! NES_UTILITY_LITERALS_HPP
