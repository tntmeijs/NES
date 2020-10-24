#ifndef NES_CPU_INSTRUCTION_OP_BCC_HPP
#define NES_CPU_INSTRUCTION_OP_BCC_HPP

#include "cpu_instruction_base.hpp"

namespace nes
{
	class CPU;

	/**
	 * Branch carry clear
	 */
	class CpuInstructionOpBCC : public CpuInstructionBase
	{
	public:
		/**
		 * Create a new BCC instruction
		 * @param	cpuRef				Reference to the CPU object
		 * @param	addressingMode		Addressing mode used for this instruction
		 */
		CpuInstructionOpBCC(CPU& cpuRef, AddressingMode addressingMode);

	protected:
		/**
		 * Perform branch if carry clear
		 */
		void ExecuteImpl() final override;
	};
}

#endif //! NES_CPU_INSTRUCTION_OP_BCC_HPP
