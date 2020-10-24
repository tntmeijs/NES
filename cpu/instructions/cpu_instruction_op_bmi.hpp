#ifndef NES_CPU_INSTRUCTION_OP_BMI_HPP
#define NES_CPU_INSTRUCTION_OP_BMI_HPP

#include "cpu_instruction_base.hpp"

namespace nes
{
	class CPU;

	/**
	 * Branch minus
	 */
	class CpuInstructionOpBMI : public CpuInstructionBase
	{
	public:
		/**
		 * Create a new BMI instruction
		 * @param	cpuRef				Reference to the CPU object
		 * @param	addressingMode		Addressing mode used for this instruction
		 */
		CpuInstructionOpBMI(CPU& cpuRef, AddressingMode addressingMode);

	protected:
		/**
		 * Perform branch if minus
		 */
		void ExecuteImpl() final override;
	};
}

#endif //! NES_CPU_INSTRUCTION_OP_BMI_HPP
