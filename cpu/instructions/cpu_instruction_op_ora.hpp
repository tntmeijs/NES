#ifndef NES_CPU_INSTRUCTION_OP_ORA_HPP
#define NES_CPU_INSTRUCTION_OP_ORA_HPP

#include "cpu_instruction_base.hpp"

namespace nes
{
	class CPU;

	/**
	 * Logical inclusive OR
	 */
	class CpuInstructionOpORA : public CpuInstructionBase
	{
	public:
		/**
		 * Create a new ORA instruction
		 * @param	cpuRef				Reference to the CPU object
		 * @param	addressingMode		Addressing mode used for this instruction
		 */
		CpuInstructionOpORA(CPU& cpuRef, AddressingMode addressingMode);

	protected:
		/**
		 * Perform logical inclusive OR
		 */
		void ExecuteImpl() final override;
	};
}

#endif //! NES_CPU_INSTRUCTION_OP_ORA_HPP
