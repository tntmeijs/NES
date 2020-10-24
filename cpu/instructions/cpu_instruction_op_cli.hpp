#ifndef NES_CPU_INSTRUCTION_OP_CLI_HPP
#define NES_CPU_INSTRUCTION_OP_CLI_HPP

#include "cpu_instruction_base.hpp"

namespace nes
{
	class CPU;

	/**
	 * Clear interrupt disable
	 */
	class CpuInstructionOpCLI : public CpuInstructionBase
	{
	public:
		/**
		 * Create a new CLI instruction
		 * @param	cpuRef				Reference to the CPU object
		 * @param	addressingMode		Addressing mode used for this instruction
		 */
		CpuInstructionOpCLI(CPU& cpuRef, AddressingMode addressingMode);

	protected:
		/**
		 * Perform clear interrupt disable
		 */
		void ExecuteImpl() final override;
	};
}

#endif //! NES_CPU_INSTRUCTION_OP_CLI_HPP
