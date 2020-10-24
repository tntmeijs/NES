#ifndef NES_CPU_INSTRUCTION_OP_BRK_HPP
#define NES_CPU_INSTRUCTION_OP_BRK_HPP

#include "cpu_instruction_base.hpp"

namespace nes
{
	class CPU;

	/**
	 * Force interrupt
	 */
	class CpuInstructionOpBRK : public CpuInstructionBase
	{
	public:
		/**
		 * Create a new BRK instruction
		 * @param	cpuRef				Reference to the CPU object
		 * @param	addressingMode		Addressing mode used for this instruction
		 */
		CpuInstructionOpBRK(CPU& cpuRef, AddressingMode addressingMode);

	protected:
		/**
		 * Perform break (force interrupt)
		 */
		void ExecuteImpl() final override;
	};
}

#endif //! NES_CPU_INSTRUCTION_OP_BRK_HPP
