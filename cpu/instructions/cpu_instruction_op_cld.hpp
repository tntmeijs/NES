#ifndef NES_CPU_INSTRUCTION_OP_CLD_HPP
#define NES_CPU_INSTRUCTION_OP_CLD_HPP

#include "cpu_instruction_base.hpp"

namespace nes
{
	class CPU;

	/**
	 * Clear decimal mode
	 */
	class CpuInstructionOpCLD : public CpuInstructionBase
	{
	public:
		/**
		 * Create a new CLD instruction
		 * @param	cpuRef				Reference to the CPU object
		 * @param	addressingMode		Addressing mode used for this instruction
		 */
		CpuInstructionOpCLD(CPU& cpuRef, AddressingMode addressingMode);

	protected:
		/**
		 * Perform clear decimal mode
		 */
		void ExecuteImpl() final override;
	};
}

#endif //! NES_CPU_INSTRUCTION_OP_CLD_HPP
