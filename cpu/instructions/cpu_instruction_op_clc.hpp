#ifndef NES_CPU_INSTRUCTION_OP_CLC_HPP
#define NES_CPU_INSTRUCTION_OP_CLC_HPP

#include "cpu_instruction_base.hpp"

namespace nes
{
	class CPU;

	/**
	 * Clear carry flag
	 */
	class CpuInstructionOpCLC : public CpuInstructionBase
	{
	public:
		/**
		 * Create a new CLC instruction
		 * @param	cpuRef				Reference to the CPU object
		 * @param	addressingMode		Addressing mode used for this instruction
		 */
		CpuInstructionOpCLC(CPU& cpuRef, AddressingMode addressingMode);

	protected:
		/**
		 * Perform clear carry flag
		 */
		void ExecuteImpl() final override;
	};
}

#endif //! NES_CPU_INSTRUCTION_OP_CLC_HPP
