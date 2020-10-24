#ifndef NES_CPU_INSTRUCTION_OP_PLP_HPP
#define NES_CPU_INSTRUCTION_OP_PLP_HPP

#include "cpu_instruction_base.hpp"

namespace nes
{
	class CPU;

	/**
	 * Pull processor status
	 */
	class CpuInstructionOpPLP : public CpuInstructionBase
	{
	public:
		/**
		 * Create a new PLP instruction
		 * @param	cpuRef				Reference to the CPU object
		 * @param	addressingMode		Addressing mode used for this instruction
		 */
		CpuInstructionOpPLP(CPU& cpuRef, AddressingMode addressingMode);

	protected:
		/**
		 * Perform pull processor status
		 */
		void ExecuteImpl() final override;
	};
}

#endif //! NES_CPU_INSTRUCTION_OP_PLP_HPP
