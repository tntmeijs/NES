#ifndef NES_CPU_INSTRUCTION_OP_INY_HPP
#define NES_CPU_INSTRUCTION_OP_INY_HPP

#include "cpu_instruction_base.hpp"

namespace nes
{
	class CPU;

	/**
	 * Increment Y register
	 */
	class CpuInstructionOpINY : public CpuInstructionBase
	{
	public:
		/**
		 * Create a new INY instruction
		 * @param	cpuRef				Reference to the CPU object
		 * @param	addressingMode		Addressing mode used for this instruction
		 */
		CpuInstructionOpINY(CPU& cpuRef, AddressingMode addressingMode);

	protected:
		/**
		 * Perform increment Y register
		 */
		void ExecuteImpl() final override;
	};
}

#endif //! NES_CPU_INSTRUCTION_OP_INY_HPP
