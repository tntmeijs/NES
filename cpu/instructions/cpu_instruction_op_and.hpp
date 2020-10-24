#ifndef NES_CPU_INSTRUCTION_OP_AND_HPP
#define NES_CPU_INSTRUCTION_OP_AND_HPP

#include "cpu_instruction_base.hpp"

namespace nes
{
	class CPU;

	/**
	 * AND operation
	 */
	class CpuInstructionOpAND : public CpuInstructionBase
	{
	public:
		/**
		 * Create a new AND instruction
		 * @param	cpuRef				Reference to the CPU object
		 * @param	addressingMode		Addressing mode used for this instruction
		 */
		CpuInstructionOpAND(CPU& cpuRef, AddressingMode addressingMode);

	protected:
		/**
		 * Perform AND operation
		 */
		void ExecuteImpl() final override;
	};
}

#endif //! NES_CPU_INSTRUCTION_OP_AND_HPP
