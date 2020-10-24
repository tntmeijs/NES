#ifndef NES_CPU_INSTRUCTION_OP_PHA_HPP
#define NES_CPU_INSTRUCTION_OP_PHA_HPP

#include "cpu_instruction_base.hpp"

namespace nes
{
	class CPU;

	/**
	 * Push accumulator
	 */
	class CpuInstructionOpPHA : public CpuInstructionBase
	{
	public:
		/**
		 * Create a new PHA instruction
		 * @param	cpuRef				Reference to the CPU object
		 * @param	addressingMode		Addressing mode used for this instruction
		 */
		CpuInstructionOpPHA(CPU& cpuRef, AddressingMode addressingMode);

	protected:
		/**
		 * Perform compare operation
		 */
		void ExecuteImpl() final override;
	};
}

#endif //! NES_CPU_INSTRUCTION_OP_PHA_HPP
