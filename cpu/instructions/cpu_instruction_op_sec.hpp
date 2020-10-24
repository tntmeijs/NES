#ifndef NES_CPU_INSTRUCTION_OP_SEC_HPP
#define NES_CPU_INSTRUCTION_OP_SEC_HPP

#include "cpu_instruction_base.hpp"

namespace nes
{
	class CPU;

	/**
	 * Set carry flag
	 */
	class CpuInstructionOpSEC : public CpuInstructionBase
	{
	public:
		/**
		 * Create a new SEC instruction
		 * @param	cpuRef				Reference to the CPU object
		 * @param	addressingMode		Addressing mode used for this instruction
		 */
		CpuInstructionOpSEC(CPU& cpuRef, AddressingMode addressingMode);

	protected:
		/**
		 * Perform set carry
		 */
		void ExecuteImpl() final override;
	};
}

#endif //! NES_CPU_INSTRUCTION_OP_SEC_HPP
