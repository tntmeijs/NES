#ifndef NES_CPU_INSTRUCTION_OP_BIT_HPP
#define NES_CPU_INSTRUCTION_OP_BIT_HPP

#include "cpu_instruction_base.hpp"

namespace nes
{
	class CPU;

	/**
	 * BIT operation
	 */
	class CpuInstructionOpBIT : public CpuInstructionBase
	{
	public:
		/**
		 * Create a new BIT instruction
		 * @param	cpuRef				Reference to the CPU object
		 * @param	addressingMode		Addressing mode used for this instruction
		 */
		CpuInstructionOpBIT(CPU& cpuRef, AddressingMode addressingMode);

	protected:
		/**
		 * Perform BIT test
		 */
		void ExecuteImpl() final override;
	};
}

#endif //! NES_CPU_INSTRUCTION_OP_BIT_HPP
