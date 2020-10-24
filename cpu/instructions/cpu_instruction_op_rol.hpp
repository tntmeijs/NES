#ifndef NES_CPU_INSTRUCTION_OP_ROL_HPP
#define NES_CPU_INSTRUCTION_OP_ROL_HPP

#include "cpu_instruction_base.hpp"

namespace nes
{
	class CPU;

	/**
	 * Rotate bits left
	 */
	class CpuInstructionOpROL : public CpuInstructionBase
	{
	public:
		/**
		 * Create a new ROL instruction
		 * @param	cpuRef				Reference to the CPU object
		 * @param	addressingMode		Addressing mode used for this instruction
		 */
		CpuInstructionOpROL(CPU& cpuRef, AddressingMode addressingMode);

	protected:
		/**
		 * Perform rotate bits left
		 */
		void ExecuteImpl() final override;
	};
}

#endif //! NES_CPU_INSTRUCTION_OP_ROL_HPP
