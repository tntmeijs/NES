#ifndef NES_CPU_INSTRUCTION_OP_BNE_HPP
#define NES_CPU_INSTRUCTION_OP_BNE_HPP

#include "cpu_instruction_base.hpp"

namespace nes
{
	class CPU;

	/**
	 * Branch not equal
	 */
	class CpuInstructionOpBNE : public CpuInstructionBase
	{
	public:
		/**
		 * Create a new BNE instruction
		 * @param	cpuRef				Reference to the CPU object
		 * @param	addressingMode		Addressing mode used for this instruction
		 */
		CpuInstructionOpBNE(CPU& cpuRef, AddressingMode addressingMode);

	protected:
		/**
		 * Perform branch if not equal
		 */
		void ExecuteImpl() final override;
	};
}

#endif //! NES_CPU_INSTRUCTION_OP_BNE_HPP
