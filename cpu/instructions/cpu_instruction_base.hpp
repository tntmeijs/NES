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
		 */
		CpuInstructionBase(CPU& cpuRef, AddressingMode addressingMode, std::string_view name);

		CpuInstructionBase(const CpuInstructionBase& other)				= default;
		CpuInstructionBase(CpuInstructionBase&& other)					= default;
		CpuInstructionBase& operator=(const CpuInstructionBase& other)	= default;
		CpuInstructionBase& operator=(CpuInstructionBase&& other)		= default;
		virtual ~CpuInstructionBase()									= default;

		/**
		 * Print debug information to the console output stream
		 */
		void PrintDebugInformation() const;

		/**
		 * Execute the instruction
		 */
		void Execute();

	protected:
		/**
		 * Override this function with the instruction's logic
		 */
		virtual void ExecuteImpl() = 0;

	protected:
		CPU& CpuRef;
		AddressingMode InstructionAddressingMode;
		std::string Name;
		std::uint8_t InstructionSize;

		// Number of cycles the instruction took
		std::uint8_t CycleCount;

		// Set to false to skip updating the program counter automatically based
		// on the instruction's size
		// This is useful for JMP instructions
		bool AutoUpdateProgramCounter;
	};
}

#endif //! NES_CPU_INSTRUCTION_BASE_HPP
