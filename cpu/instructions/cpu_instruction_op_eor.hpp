#ifndef NES_CPU_INSTRUCTION_OP_EOR_HPP
#define NES_CPU_INSTRUCTION_OP_EOR_HPP

#include "cpu_instruction_base.hpp"

namespace nes
{
	class CPU;

	/**
	 * Exclusive OR
	 */
	class CpuInstructionOpEOR : public CpuInstructionBase
	{
	public:
		/**
		 * Create a new EOR instruction
		 * @param	cpuRef				Reference to the CPU object
		 * @param	addressingMode		Addressing mode used for this instruction
		 */
		CpuInstructionOpEOR(CPU& cpuRef, AddressingMode addressingMode);

	protected:
		/**
		 * Perform exclusive OR
		 */
		void ExecuteImpl() final override;
	};
}

#endif //! NES_CPU_INSTRUCTION_OP_EOR_HPP
