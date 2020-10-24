#ifndef NES_CPU_INSTRUCTION_OP_PLA_HPP
#define NES_CPU_INSTRUCTION_OP_PLA_HPP

#include "cpu_instruction_base.hpp"

namespace nes
{
	class CPU;

	/**
	 * Pull accumulator
	 */
	class CpuInstructionOpPLA : public CpuInstructionBase
	{
	public:
		/**
		 * Create a new PLA instruction
		 * @param	cpuRef				Reference to the CPU object
		 * @param	addressingMode		Addressing mode used for this instruction
		 */
		CpuInstructionOpPLA(CPU& cpuRef, AddressingMode addressingMode);

	protected:
		/**
		 * Perform pull accumulator
		 */
		void ExecuteImpl() final override;
	};
}

#endif //! NES_CPU_INSTRUCTION_OP_PLA_HPP
