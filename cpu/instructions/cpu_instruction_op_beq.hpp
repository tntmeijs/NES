#ifndef NES_CPU_INSTRUCTION_OP_BEQ_HPP
#define NES_CPU_INSTRUCTION_OP_BEQ_HPP

#include "cpu_instruction_base.hpp"

namespace nes
{
	class CPU;

	/**
	 * Branch equal
	 */
	class CpuInstructionOpBEQ : public CpuInstructionBase
	{
	public:
		/**
		 * Create a new BEQ instruction
		 * @param	cpuRef				Reference to the CPU object
		 * @param	addressingMode		Addressing mode used for this instruction
		 */
		CpuInstructionOpBEQ(CPU& cpuRef, AddressingMode addressingMode);

	protected:
		/**
		 * Perform branch if equal
		 */
		void ExecuteImpl() final override;
	};
}

#endif //! NES_CPU_INSTRUCTION_OP_ADC_HPP
