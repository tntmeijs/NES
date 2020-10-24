#ifndef NES_CPU_INSTRUCTION_OP_NOP_HPP
#define NES_CPU_INSTRUCTION_OP_NOP_HPP

#include "cpu_instruction_base.hpp"

namespace nes
{
	class CPU;

	/**
	 * No operation
	 */
	class CpuInstructionOpNOP : public CpuInstructionBase
	{
	public:
		/**
		 * Create a new NOP instruction
		 * @param	cpuRef				Reference to the CPU object
		 * @param	addressingMode		Addressing mode used for this instruction
		 */
		CpuInstructionOpNOP(CPU& cpuRef, AddressingMode addressingMode);

	protected:
		/**
		 * Perform no operation
		 */
		void ExecuteImpl() final override;
	};
}

#endif //! NES_CPU_INSTRUCTION_OP_NOP_HPP
