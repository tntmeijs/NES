#ifndef NES_CPU_INSTRUCTION_OP_TXA_HPP
#define NES_CPU_INSTRUCTION_OP_TXA_HPP

#include "cpu_instruction_base.hpp"

namespace nes
{
	class CPU;

	/**
	 * Transfer X register to accumulator
	 */
	class CpuInstructionOpTXA : public CpuInstructionBase
	{
	public:
		/**
		 * Create a new TXA instruction
		 * @param	cpuRef				Reference to the CPU object
		 * @param	addressingMode		Addressing mode used for this instruction
		 */
		CpuInstructionOpTXA(CPU& cpuRef, AddressingMode addressingMode);

	protected:
		/**
		 * Perform transfer X to accumulator
		 */
		void ExecuteImpl() final override;
	};
}

#endif //! NES_CPU_INSTRUCTION_OP_TXA_HPP
