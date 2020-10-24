#ifndef NES_CPU_INSTRUCTION_OP_STA_HPP
#define NES_CPU_INSTRUCTION_OP_STA_HPP

#include "cpu_instruction_base.hpp"

namespace nes
{
	class CPU;

	/**
	 * Store accumulator
	 */
	class CpuInstructionOpSTA : public CpuInstructionBase
	{
	public:
		/**
		 * Create a new STA instruction
		 * @param	cpuRef				Reference to the CPU object
		 * @param	addressingMode		Addressing mode used for this instruction
		 */
		CpuInstructionOpSTA(CPU& cpuRef, AddressingMode addressingMode);

	protected:
		/**
		 * Perform store accumulator
		 */
		void ExecuteImpl() final override;
	};
}

#endif //! NES_CPU_INSTRUCTION_OP_STA_HPP
