#ifndef NES_CPU_INSTRUCTION_OP_TAX_HPP
#define NES_CPU_INSTRUCTION_OP_TAX_HPP

#include "cpu_instruction_base.hpp"

namespace nes
{
	class CPU;

	/**
	 * Transfer accumulator to X register
	 */
	class CpuInstructionOpTAX : public CpuInstructionBase
	{
	public:
		/**
		 * Create a new TAX instruction
		 * @param	cpuRef				Reference to the CPU object
		 * @param	addressingMode		Addressing mode used for this instruction
		 */
		CpuInstructionOpTAX(CPU& cpuRef, AddressingMode addressingMode);

	protected:
		/**
		 * Perform transfer accumulator to X
		 */
		void ExecuteImpl() final override;
	};
}

#endif //! NES_CPU_INSTRUCTION_OP_TAX_HPP
