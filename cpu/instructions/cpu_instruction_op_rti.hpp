#ifndef NES_CPU_INSTRUCTION_OP_RTI_HPP
#define NES_CPU_INSTRUCTION_OP_RTI_HPP

#include "cpu_instruction_base.hpp"

namespace nes
{
	class CPU;

	/**
	 * Return from interrupt
	 */
	class CpuInstructionOpRTI : public CpuInstructionBase
	{
	public:
		/**
		 * Create a new RTI instruction
		 * @param	cpuRef				Reference to the CPU object
		 * @param	addressingMode		Addressing mode used for this instruction
		 */
		CpuInstructionOpRTI(CPU& cpuRef, AddressingMode addressingMode);

	protected:
		/**
		 * Perform return from interrupt
		 */
		void ExecuteImpl() final override;
	};
}

#endif //! NES_CPU_INSTRUCTION_OP_RTI_HPP
