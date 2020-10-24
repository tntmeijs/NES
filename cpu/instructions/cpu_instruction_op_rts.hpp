#ifndef NES_CPU_INSTRUCTION_OP_RTS_HPP
#define NES_CPU_INSTRUCTION_OP_RTS_HPP

#include "cpu_instruction_base.hpp"

namespace nes
{
	class CPU;

	/**
	 * Return from subroutine
	 */
	class CpuInstructionOpRTS : public CpuInstructionBase
	{
	public:
		/**
		 * Create a new RTS instruction
		 * @param	cpuRef				Reference to the CPU object
		 * @param	addressingMode		Addressing mode used for this instruction
		 */
		CpuInstructionOpRTS(CPU& cpuRef, AddressingMode addressingMode);

	protected:
		/**
		 * Perform return from subroutine
		 */
		void ExecuteImpl() final override;
	};
}

#endif //! NES_CPU_INSTRUCTION_OP_RTS_HPP
