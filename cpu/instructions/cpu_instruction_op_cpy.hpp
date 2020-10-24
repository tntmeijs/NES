#ifndef NES_CPU_INSTRUCTION_OP_CPY_HPP
#define NES_CPU_INSTRUCTION_OP_CPY_HPP

#include "cpu_instruction_base.hpp"

namespace nes
{
	class CPU;

	/**
	 * Compare Y register
	 */
	class CpuInstructionOpCPY : public CpuInstructionBase
	{
	public:
		/**
		 * Create a new CPY instruction
		 * @param	cpuRef				Reference to the CPU object
		 * @param	addressingMode		Addressing mode used for this instruction
		 */
		CpuInstructionOpCPY(CPU& cpuRef, AddressingMode addressingMode);

	protected:
		/**
		 * Perform compare Y register
		 */
		void ExecuteImpl() final override;
	};
}

#endif //! NES_CPU_INSTRUCTION_OP_CPY_HPP
