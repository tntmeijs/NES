#ifndef NES_CPU_INSTRUCTION_OP_CMP_HPP
#define NES_CPU_INSTRUCTION_OP_CMP_HPP

#include "cpu_instruction_base.hpp"

namespace nes
{
	class CPU;

	/**
	 * Compare operation
	 */
	class CpuInstructionOpCMP : public CpuInstructionBase
	{
	public:
		/**
		 * Create a new CMP instruction
		 * @param	cpuRef				Reference to the CPU object
		 * @param	addressingMode		Addressing mode used for this instruction
		 */
		CpuInstructionOpCMP(CPU& cpuRef, AddressingMode addressingMode);

	protected:
		/**
		 * Perform compare operation
		 */
		void ExecuteImpl() final override;
	};
}

#endif //! NES_CPU_INSTRUCTION_OP_CMP_HPP
