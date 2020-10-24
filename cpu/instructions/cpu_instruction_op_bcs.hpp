#ifndef NES_CPU_INSTRUCTION_OP_BCS_HPP
#define NES_CPU_INSTRUCTION_OP_BCS_HPP

#include "cpu_instruction_base.hpp"

namespace nes
{
	class CPU;

	/**
	 * Branch carry set
	 */
	class CpuInstructionOpBCS : public CpuInstructionBase
	{
	public:
		/**
		 * Create a new BCS instruction
		 * @param	cpuRef				Reference to the CPU object
		 * @param	addressingMode		Addressing mode used for this instruction
		 */
		CpuInstructionOpBCS(CPU& cpuRef, AddressingMode addressingMode);

	protected:
		/**
		 * Perform branch if carry set
		 */
		void ExecuteImpl() final override;
	};
}

#endif //! NES_CPU_INSTRUCTION_OP_BCS_HPP
