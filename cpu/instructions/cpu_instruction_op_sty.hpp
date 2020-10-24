#ifndef NES_CPU_INSTRUCTION_OP_STY_HPP
#define NES_CPU_INSTRUCTION_OP_STY_HPP

#include "cpu_instruction_base.hpp"

namespace nes
{
	class CPU;

	/**
	 * Store Y register
	 */
	class CpuInstructionOpSTY : public CpuInstructionBase
	{
	public:
		/**
		 * Create a new STY instruction
		 * @param	cpuRef				Reference to the CPU object
		 * @param	addressingMode		Addressing mode used for this instruction
		 */
		CpuInstructionOpSTY(CPU& cpuRef, AddressingMode addressingMode);

	protected:
		/**
		 * Perform store Y register
		 */
		void ExecuteImpl() final override;
	};
}

#endif //! NES_CPU_INSTRUCTION_OP_STY_HPP
