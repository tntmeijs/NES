#ifndef NES_CPU_INSTRUCTION_OP_INC_HPP
#define NES_CPU_INSTRUCTION_OP_INC_HPP

#include "cpu_instruction_base.hpp"

namespace nes
{
	class CPU;

	/**
	 * Increment memory
	 */
	class CpuInstructionOpINC : public CpuInstructionBase
	{
	public:
		/**
		 * Create a new INC instruction
		 * @param	cpuRef				Reference to the CPU object
		 * @param	addressingMode		Addressing mode used for this instruction
		 */
		CpuInstructionOpINC(CPU& cpuRef, AddressingMode addressingMode);

	protected:
		/**
		 * Perform increment memory
		 */
		void ExecuteImpl() final override;
	};
}

#endif //! NES_CPU_INSTRUCTION_OP_INC_HPP
