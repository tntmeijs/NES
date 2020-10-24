#ifndef NES_CPU_INSTRUCTION_OP_SEI_HPP
#define NES_CPU_INSTRUCTION_OP_SEI_HPP

#include "cpu_instruction_base.hpp"

namespace nes
{
	class CPU;

	/**
	 * Set interrupt disable flag
	 */
	class CpuInstructionOpSEI : public CpuInstructionBase
	{
	public:
		/**
		 * Create a new SEI instruction
		 * @param	cpuRef				Reference to the CPU object
		 * @param	addressingMode		Addressing mode used for this instruction
		 */
		CpuInstructionOpSEI(CPU& cpuRef, AddressingMode addressingMode);

	protected:
		/**
		 * Perform interrupt disable
		 */
		void ExecuteImpl() final override;
	};
}

#endif //! NES_CPU_INSTRUCTION_OP_SEI_HPP
