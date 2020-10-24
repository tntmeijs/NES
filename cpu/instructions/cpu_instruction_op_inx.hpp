#ifndef NES_CPU_INSTRUCTION_OP_INX_HPP
#define NES_CPU_INSTRUCTION_OP_INX_HPP

#include "cpu_instruction_base.hpp"

namespace nes
{
	class CPU;

	/**
	 * Increment X register
	 */
	class CpuInstructionOpINX : public CpuInstructionBase
	{
	public:
		/**
		 * Create a new INX instruction
		 * @param	cpuRef				Reference to the CPU object
		 * @param	addressingMode		Addressing mode used for this instruction
		 */
		CpuInstructionOpINX(CPU& cpuRef, AddressingMode addressingMode);

	protected:
		/**
		 * Perform increment X register
		 */
		void ExecuteImpl() final override;
	};
}

#endif //! NES_CPU_INSTRUCTION_OP_INX_HPP
