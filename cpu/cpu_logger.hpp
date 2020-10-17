#ifndef NES_CPU_LOGGER_HPP
#define NES_CPU_LOGGER_HPP

#include <cstdint>
#include <fstream>
#include <sstream>
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
		 * Utility function to help construct a string stream object that holds
		 * information about the current CPU instruction and the state of the CPU
		 * @param	cpuRef	Reference to the CPU
		 * @param	opName	Name of the current operation
		 * @param	opSize	Number of bytes used by the current operation
		 * @return	String stream object with debug information
		 */
		static std::stringstream ConstructStreamFromData(const CPU& cpuRef, std::string_view opName, std::uint8_t opSize);

	public:
		/**
		 * Create a new CPU logger object
		 * @param	cpuRef	Reference to the CPU to log the data for
		 * @param	ramRef	RAM object used by the CPU
		 */
		CpuLogger(const CPU& cpuRef, const RAM& ramRef);

		/**
		 * Copy constructor
		 * @param	other	Other instance
		 */
		CpuLogger(const CpuLogger& other) = default;

		/**
		 * Move constructor
		 * @param	other	Other instance
		 */
		CpuLogger(CpuLogger&& other) = default;

		/**
		 * Copy assignment operator
		 * @param	other	Other instance
		 */
		CpuLogger& operator=(const CpuLogger& other) = default;

		/**
		 * Move assignment operator
		 * @param	other	Other instance
		 */
		CpuLogger& operator=(CpuLogger&& other) = default;

		/**
		 * Close the file handle
		 */
		~CpuLogger();

		/**
		 * Call this function before actually executing the instruction
		 * This function will log the state of the CPU to the console
		 * 
		 * The formatting in this function seems strange at first glance, but
		 * we chose this format to make it easy to match the output of the log
		 * against the NESTEST rom result:
		 * https://www.qmtpro.com/~nes/misc/nestest.log
		 * 
		 * @param	name	Name of the instruction to execute
		 * @param	num		Number of bytes this instruction uses
		 */
		void LogOperation(std::string_view name, std::uint8_t num);

	private:
		const CPU& CpuRef;
		const RAM& RamRef;

		std::ofstream LogFile;
	};
}

#endif //! NES_CPU_LOGGER_HPP
