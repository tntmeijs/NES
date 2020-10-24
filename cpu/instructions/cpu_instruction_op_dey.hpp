#ifndef NES_CPU_INSTRUCTION_OP_DEY_HPP
#define NES_CPU_INSTRUCTION_OP_DEY_HPP

#include "cpu_instruction_base.hpp"

namespace nes
{
	class CPU;

	/**
	 * Decrement Y register
	 */
	class CpuInstructionOpDEY : public CpuInstructionBase
	{
	public:
		/**
		 * Create a new DEY instruction
		 * @param	cpuRef				Reference to the CPU object
		 * @param	addressingMode		Addressing mode used for this instruction
		 */
		CpuInstructionOpDEY(CPU& cpuRef, AddressingMode addressingMode);

	protected:
		/**
		 * Perform decrement Y register
		 */
		void ExecuteImpl() final override;
	};
}

#endif //! NES_CPU_INSTRUCTION_OP_DEY_HPP
