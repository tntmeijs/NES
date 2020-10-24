#ifndef NES_CPU_INSTRUCTION_OP_JSR_HPP
#define NES_CPU_INSTRUCTION_OP_JSR_HPP

#include "cpu_instruction_base.hpp"

namespace nes
{
	class CPU;

	/**
	 * Jump to subroutine
	 */
	class CpuInstructionOpJSR : public CpuInstructionBase
	{
	public:
		/**
		 * Create a new JSR instruction
		 * @param	cpuRef				Reference to the CPU object
		 * @param	addressingMode		Addressing mode used for this instruction
		 */
		CpuInstructionOpJSR(CPU& cpuRef, AddressingMode addressingMode);

	protected:
		/**
		 * Perform jump to subroutine
		 */
		void ExecuteImpl() final override;
	};
}

#endif //! NES_CPU_INSTRUCTION_OP_JSR_HPP
