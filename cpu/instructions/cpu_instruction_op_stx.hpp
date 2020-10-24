#ifndef NES_CPU_INSTRUCTION_OP_STX_HPP
#define NES_CPU_INSTRUCTION_OP_STX_HPP

#include "cpu_instruction_base.hpp"

namespace nes
{
	class CPU;

	/**
	 * Store X register
	 */
	class CpuInstructionOpSTX : public CpuInstructionBase
	{
	public:
		/**
		 * Create a new STX instruction
		 * @param	cpuRef				Reference to the CPU object
		 * @param	addressingMode		Addressing mode used for this instruction
		 */
		CpuInstructionOpSTX(CPU& cpuRef, AddressingMode addressingMode);

	protected:
		/**
		 * Perform store X register
		 */
		void ExecuteImpl() final override;
	};
}

#endif //! NES_CPU_INSTRUCTION_OP_STX_HPP
