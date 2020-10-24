#ifndef NES_CPU_INSTRUCTION_OP_TSX_HPP
#define NES_CPU_INSTRUCTION_OP_TSX_HPP

#include "cpu_instruction_base.hpp"

namespace nes
{
	class CPU;

	/**
	 * Transfer stack pointer to X register
	 */
	class CpuInstructionOpTSX : public CpuInstructionBase
	{
	public:
		/**
		 * Create a new TSX instruction
		 * @param	cpuRef				Reference to the CPU object
		 * @param	addressingMode		Addressing mode used for this instruction
		 */
		CpuInstructionOpTSX(CPU& cpuRef, AddressingMode addressingMode);

	protected:
		/**
		 * Perform transfer stack pointer to X
		 */
		void ExecuteImpl() final override;
	};
}

#endif //! NES_CPU_INSTRUCTION_OP_TSX_HPP
