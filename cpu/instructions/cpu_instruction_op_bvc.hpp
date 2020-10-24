#ifndef NES_CPU_INSTRUCTION_OP_BVC_HPP
#define NES_CPU_INSTRUCTION_OP_BVC_HPP

#include "cpu_instruction_base.hpp"

namespace nes
{
	class CPU;

	/**
	 * Branch overflow clear
	 */
	class CpuInstructionOpBVC : public CpuInstructionBase
	{
	public:
		/**
		 * Create a new BVC instruction
		 * @param	cpuRef				Reference to the CPU object
		 * @param	addressingMode		Addressing mode used for this instruction
		 */
		CpuInstructionOpBVC(CPU& cpuRef, AddressingMode addressingMode);

	protected:
		/**
		 * Perform branch if overflow clear
		 */
		void ExecuteImpl() final override;
	};
}

#endif //! NES_CPU_INSTRUCTION_OP_BVC_HPP
