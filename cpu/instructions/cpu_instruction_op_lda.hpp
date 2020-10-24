#ifndef NES_CPU_INSTRUCTION_OP_LDA_HPP
#define NES_CPU_INSTRUCTION_OP_LDA_HPP

#include "cpu_instruction_base.hpp"

namespace nes
{
	class CPU;

	/**
	 * Load accumulator
	 */
	class CpuInstructionOpLDA : public CpuInstructionBase
	{
	public:
		/**
		 * Create a new LDA instruction
		 * @param	cpuRef				Reference to the CPU object
		 * @param	addressingMode		Addressing mode used for this instruction
		 */
		CpuInstructionOpLDA(CPU& cpuRef, AddressingMode addressingMode);

	protected:
		/**
		 * Perform load accumulator
		 */
		void ExecuteImpl() final override;
	};
}

#endif //! NES_CPU_INSTRUCTION_OP_LDA_HPP
