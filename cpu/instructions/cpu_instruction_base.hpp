#ifndef NES_CPU_INSTRUCTION_BASE_HPP
#define NES_CPU_INSTRUCTION_BASE_HPP

#include "cpu_instruction_addressing_mode.hpp"

#include <cstdint>
#include <string>
#include <string_view>

namespace nes
{
	class CPU;

	/**
	 * Abstract base class for each CPU instruction
	 */
	class CpuInstructionBase
	{
	public:
		/**
		 * Create a new CPU instruction
		 * @param	cpuRef				Reference to the CPU object
		 * @param	addressingMode		Addressing mode used for this instruction
		 * @param	name				Name of this instruction for debugging purposes
		 * @param	size				Number of bytes used by this instruction
		 */
		CpuInstructionBase(CPU& cpuRef, AddressingMode addressingMode, std::string_view name, std::uint8_t size);

		CpuInstructionBase(const CpuInstructionBase& other)				= default;
		CpuInstructionBase(CpuInstructionBase&& other)					= default;
		CpuInstructionBase& operator=(const CpuInstructionBase& other)	= default;
		CpuInstructionBase& operator=(CpuInstructionBase&& other)		= default;
		virtual ~CpuInstructionBase()									= default;

		/**
		 * Print debug information to the console output stream
		 */
		void PrintDebugInformation();

		/**
		 * Override this function with the instruction's logic
		 */
		virtual void Execute() = 0;

	protected:
		CPU& CpuRef;
		AddressingMode InstructionAddressingMode;
		std::string Name;
		std::uint8_t InstructionSize;
	};
}

#endif //! NES_CPU_INSTRUCTION_BASE_HPP
