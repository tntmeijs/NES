#ifndef NES_CPU_INSTRUCTION_OP_TXS_HPP
#define NES_CPU_INSTRUCTION_OP_TXS_HPP

#include "cpu_instruction_base.hpp"

namespace nes
{
	class CPU;

	/**
	 * Transfer X register to stack pointer
	 */
	class CpuInstructionOpTXS : public CpuInstructionBase
	{
	public:
		/**
		 * Create a new TXS instruction
		 * @param	cpuRef				Reference to the CPU object
		 * @param	addressingMode		Addressing mode used for this instruction
		 */
		CpuInstructionOpTXS(CPU& cpuRef, AddressingMode addressingMode);

	protected:
		/**
		 * Perform transfer X to stack pointer
		 */
		void ExecuteImpl() final override;
	};
}

#endif //! NES_CPU_INSTRUCTION_OP_TXS_HPP
