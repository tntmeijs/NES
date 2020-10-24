#ifndef NES_CPU_INSTRUCTION_OP_DEX_HPP
#define NES_CPU_INSTRUCTION_OP_DEX_HPP

#include "cpu_instruction_base.hpp"

namespace nes
{
	class CPU;

	/**
	 * //
	 */
	class CpuInstructionOpDEX : public CpuInstructionBase
	{
	public:
		/**
		 * Create a new DEX instruction
		 * @param	cpuRef				Reference to the CPU object
		 * @param	addressingMode		Addressing mode used for this instruction
		 */
		CpuInstructionOpDEX(CPU& cpuRef, AddressingMode addressingMode);

	protected:
		/**
		 * Perform compare operation
		 */
		void ExecuteImpl() final override;
	};
}

#endif //! NES_CPU_INSTRUCTION_OP_DEX_HPP
