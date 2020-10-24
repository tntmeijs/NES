#ifndef NES_CPU_INSTRUCTION_OP_TYA_HPP
#define NES_CPU_INSTRUCTION_OP_TYA_HPP

#include "cpu_instruction_base.hpp"

namespace nes
{
	class CPU;

	/**
	 * Transfer Y register to accumulator
	 */
	class CpuInstructionOpTYA : public CpuInstructionBase
	{
	public:
		/**
		 * Create a new TYA instruction
		 * @param	cpuRef				Reference to the CPU object
		 * @param	addressingMode		Addressing mode used for this instruction
		 */
		CpuInstructionOpTYA(CPU& cpuRef, AddressingMode addressingMode);

	protected:
		/**
		 * Perform transfer Y to accumulator
		 */
		void ExecuteImpl() final override;
	};
}

#endif //! NES_CPU_INSTRUCTION_OP_TYA_HPP
