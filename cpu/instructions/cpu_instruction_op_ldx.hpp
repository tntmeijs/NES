#ifndef NES_CPU_INSTRUCTION_OP_LDX_HPP
#define NES_CPU_INSTRUCTION_OP_LDX_HPP

#include "cpu_instruction_base.hpp"

namespace nes
{
	class CPU;

	/**
	 * Load X register
	 */
	class CpuInstructionOpLDX : public CpuInstructionBase
	{
	public:
		/**
		 * Create a new LDX instruction
		 * @param	cpuRef				Reference to the CPU object
		 * @param	addressingMode		Addressing mode used for this instruction
		 */
		CpuInstructionOpLDX(CPU& cpuRef, AddressingMode addressingMode);

	protected:
		/**
		 * Perform load X register
		 */
		void ExecuteImpl() final override;
	};
}

#endif //! NES_CPU_INSTRUCTION_OP_LDX_HPP
