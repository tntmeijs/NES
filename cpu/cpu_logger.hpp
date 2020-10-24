#ifndef NES_CPU_LOGGER_HPP
#define NES_CPU_LOGGER_HPP

#include <cstdint>
#include <sstream>
#include <string_view>

namespace nes
{
	class CPU;

	/**
	 * Logs the CPU state to the console
	 */
	class CpuLogger
	{
	public:
		/**
		 * Utility function to help construct a string stream object that holds
		 * information about the current CPU instruction and the state of the CPU
		 * @param	cpuRef	Reference to the CPU
		 * @param	opName	Name of the current operation
		 * @param	opSize	Number of bytes used by the current operation
		 * @return	String stream object with debug information
		 */
		static std::stringstream ConstructStreamFromData(const CPU& cpuRef, std::string_view opName, std::uint8_t opSize);
	};
}

#endif //! NES_CPU_LOGGER_HPP
