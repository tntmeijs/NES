#ifndef NES_CPU_INSTRUCTION_OP_SBC_HPP
#define NES_CPU_INSTRUCTION_OP_SBC_HPP

#include "cpu_instruction_base.hpp"

namespace nes
{
	class CPU;

	/**
	 * Subtract with carry
	 */
	class CpuInstructionOpSBC : public CpuInstructionBase
	{
	public:
		/**
		 * Create a new SBC instruction
		 * @param	cpuRef				Reference to the CPU object
		 * @param	addressingMode		Addressing mode used for this instruction
		 */
		CpuInstructionOpSBC(CPU& cpuRef, AddressingMode addressingMode);

	protected:
		/**
		 * Perform subtract with carry
		 */
		void ExecuteImpl() final override;
	};
}

#endif //! NES_CPU_INSTRUCTION_OP_SBC_HPP
