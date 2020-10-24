#ifndef NES_CPU_INSTRUCTION_OP_ROR_HPP
#define NES_CPU_INSTRUCTION_OP_ROR_HPP

#include "cpu_instruction_base.hpp"

namespace nes
{
	class CPU;

	/**
	 * Rotate bits right
	 */
	class CpuInstructionOpROR : public CpuInstructionBase
	{
	public:
		/**
		 * Create a new ROR instruction
		 * @param	cpuRef				Reference to the CPU object
		 * @param	addressingMode		Addressing mode used for this instruction
		 */
		CpuInstructionOpROR(CPU& cpuRef, AddressingMode addressingMode);

	protected:
		/**
		 * Perform rotate bits right
		 */
		void ExecuteImpl() final override;
	};
}

#endif //! NES_CPU_INSTRUCTION_OP_ROR_HPP
