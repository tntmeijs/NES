#ifndef NES_CPU_INSTRUCTION_OP_CPX_HPP
#define NES_CPU_INSTRUCTION_OP_CPX_HPP

#include "cpu_instruction_base.hpp"

namespace nes
{
	class CPU;

	/**
	 * Compare X register
	 */
	class CpuInstructionOpCPX : public CpuInstructionBase
	{
	public:
		/**
		 * Create a new CPX instruction
		 * @param	cpuRef				Reference to the CPU object
		 * @param	addressingMode		Addressing mode used for this instruction
		 */
		CpuInstructionOpCPX(CPU& cpuRef, AddressingMode addressingMode);

	protected:
		/**
		 * Perform compare X register
		 */
		void ExecuteImpl() final override;
	};
}

#endif //! NES_CPU_INSTRUCTION_OP_CPX_HPP
