#ifndef NES_CPU_INSTRUCTION_OP_LDY_HPP
#define NES_CPU_INSTRUCTION_OP_LDY_HPP

#include "cpu_instruction_base.hpp"

namespace nes
{
	class CPU;

	/**
	 * Load Y register
	 */
	class CpuInstructionOpLDY : public CpuInstructionBase
	{
	public:
		/**
		 * Create a new LDY instruction
		 * @param	cpuRef				Reference to the CPU object
		 * @param	addressingMode		Addressing mode used for this instruction
		 */
		CpuInstructionOpLDY(CPU& cpuRef, AddressingMode addressingMode);

	protected:
		/**
		 * Perform load Y register
		 */
		void ExecuteImpl() final override;
	};
}

#endif //! NES_CPU_INSTRUCTION_OP_LDY_HPP
