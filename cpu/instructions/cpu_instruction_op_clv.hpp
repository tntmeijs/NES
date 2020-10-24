#ifndef NES_CPU_INSTRUCTION_OP_CLV_HPP
#define NES_CPU_INSTRUCTION_OP_CLV_HPP

#include "cpu_instruction_base.hpp"

namespace nes
{
	class CPU;

	/**
	 * Clear overflow flag
	 */
	class CpuInstructionOpCLV : public CpuInstructionBase
	{
	public:
		/**
		 * Create a new CLV instruction
		 * @param	cpuRef				Reference to the CPU object
		 * @param	addressingMode		Addressing mode used for this instruction
		 */
		CpuInstructionOpCLV(CPU& cpuRef, AddressingMode addressingMode);

	protected:
		/**
		 * Perform clear overflow flag
		 */
		void ExecuteImpl() final override;
	};
}

#endif //! NES_CPU_INSTRUCTION_OP_CLV_HPP
