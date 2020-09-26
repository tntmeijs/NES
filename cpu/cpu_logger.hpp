#ifndef NES_CPU_LOGGER_HPP
#define NES_CPU_LOGGER_HPP

#include <cstdint>
#include <string_view>

namespace nes
{
	class CPU;
	class RAM;

	/**
	 * Logs the CPU state to the console
	 */
	class CpuLogger
	{
	public:
		/**
		 * Create a new CPU logger object
		 * @param	cpuRef	Reference to the CPU to log the data for
		 * @param	ramRef	RAM object used by the CPU
		 */
		CpuLogger(const CPU& cpuRef, const RAM& ramRef);

		/**
		 * Call this function before actually executing the instruction
		 * This function will log the state of the CPU to the console
		 * @param	name	Name of the instruction to execute
		 * @param	num		Number of bytes this instruction uses
		 */
		void LogOperation(std::string_view name, std::uint8_t num);

	private:
		const CPU& CpuRef;
		const RAM& RamRef;
	};
}

#endif //! NES_CPU_LOGGER_HPP
