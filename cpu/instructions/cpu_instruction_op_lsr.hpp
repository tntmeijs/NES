#ifndef NES_CPU_INSTRUCTION_OP_LSR_HPP
#define NES_CPU_INSTRUCTION_OP_LSR_HPP

#include "cpu_instruction_base.hpp"

namespace nes
{
	class CPU;

	/**
	 * Logical shift right
	 */
	class CpuInstructionOpLSR : public CpuInstructionBase
	{
	public:
		/**
		 * Create a new LSR instruction
		 * @param	cpuRef				Reference to the CPU object
		 * @param	addressingMode		Addressing mode used for this instruction
		 */
		CpuInstructionOpLSR(CPU& cpuRef, AddressingMode addressingMode);

	protected:
		/**
		 * Perform logical shift right
		 */
		void ExecuteImpl() final override;
	};
}

#endif //! NES_CPU_INSTRUCTION_OP_LSR_HPP
