#ifndef NES_CPU_INSTRUCTION_OP_BPL_HPP
#define NES_CPU_INSTRUCTION_OP_BPL_HPP

#include "cpu_instruction_base.hpp"

namespace nes
{
	class CPU;

	/**
	 * Branch plus
	 */
	class CpuInstructionOpBPL : public CpuInstructionBase
	{
	public:
		/**
		 * Create a new BPL instruction
		 * @param	cpuRef				Reference to the CPU object
		 * @param	addressingMode		Addressing mode used for this instruction
		 */
		CpuInstructionOpBPL(CPU& cpuRef, AddressingMode addressingMode);

	protected:
		/**
		 * Perform branch if positive
		 */
		void ExecuteImpl() final override;
	};
}

#endif //! NES_CPU_INSTRUCTION_OP_BPL_HPP
