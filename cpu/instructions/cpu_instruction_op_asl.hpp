#ifndef NES_CPU_INSTRUCTION_OP_ASL_HPP
#define NES_CPU_INSTRUCTION_OP_ASL_HPP

#include "cpu_instruction_base.hpp"

namespace nes
{
	class CPU;

	/**
	 * Arithmetic shift left
	 */
	class CpuInstructionOpASL : public CpuInstructionBase
	{
	public:
		/**
		 * Create a new ASL instruction
		 * @param	cpuRef				Reference to the CPU object
		 * @param	addressingMode		Addressing mode used for this instruction
		 */
		CpuInstructionOpASL(CPU& cpuRef, AddressingMode addressingMode);

	protected:
		/**
		 * Perform arithmetic shift left
		 */
		void ExecuteImpl() final override;
	};
}

#endif //! NES_CPU_INSTRUCTION_OP_ASL_HPP
