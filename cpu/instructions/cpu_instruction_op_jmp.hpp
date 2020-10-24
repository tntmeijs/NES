#ifndef NES_CPU_INSTRUCTION_OP_JMP_HPP
#define NES_CPU_INSTRUCTION_OP_JMP_HPP

#include "cpu_instruction_base.hpp"

namespace nes
{
	class CPU;

	/**
	 * Jump
	 */
	class CpuInstructionOpJMP : public CpuInstructionBase
	{
	public:
		/**
		 * Create a new JMP instruction
		 * @param	cpuRef				Reference to the CPU object
		 * @param	addressingMode		Addressing mode used for this instruction
		 */
		CpuInstructionOpJMP(CPU& cpuRef, AddressingMode addressingMode);

	protected:
		/**
		 * Perform jump
		 */
		void ExecuteImpl() final override;
	};
}

#endif //! NES_CPU_INSTRUCTION_OP_JMP_HPP
