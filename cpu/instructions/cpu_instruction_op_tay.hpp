#ifndef NES_CPU_INSTRUCTION_OP_TAY_HPP
#define NES_CPU_INSTRUCTION_OP_TAY_HPP

#include "cpu_instruction_base.hpp"

namespace nes
{
	class CPU;

	/**
	 * Transfer accumulator to Y register
	 */
	class CpuInstructionOpTAY : public CpuInstructionBase
	{
	public:
		/**
		 * Create a new TAY instruction
		 * @param	cpuRef				Reference to the CPU object
		 * @param	addressingMode		Addressing mode used for this instruction
		 */
		CpuInstructionOpTAY(CPU& cpuRef, AddressingMode addressingMode);

	protected:
		/**
		 * Perform transfer accumulator to Y
		 */
		void ExecuteImpl() final override;
	};
}

#endif //! NES_CPU_INSTRUCTION_OP_TAY_HPP
