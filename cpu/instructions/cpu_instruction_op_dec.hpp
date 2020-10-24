#ifndef NES_CPU_INSTRUCTION_OP_DEC_HPP
#define NES_CPU_INSTRUCTION_OP_DEC_HPP

#include "cpu_instruction_base.hpp"

namespace nes
{
	class CPU;

	/**
	 * Decrement memory
	 */
	class CpuInstructionOpDEC : public CpuInstructionBase
	{
	public:
		/**
		 * Create a new DEC instruction
		 * @param	cpuRef				Reference to the CPU object
		 * @param	addressingMode		Addressing mode used for this instruction
		 */
		CpuInstructionOpDEC(CPU& cpuRef, AddressingMode addressingMode);

	protected:
		/**
		 * Perform decrement memory
		 */
		void ExecuteImpl() final override;
	};
}

#endif //! NES_CPU_INSTRUCTION_OP_DEC_HPP
