#ifndef NES_CPU_INSTRUCTION_OP_SED_HPP
#define NES_CPU_INSTRUCTION_OP_SED_HPP

#include "cpu_instruction_base.hpp"

namespace nes
{
	class CPU;

	/**
	 * Set decimal flag
	 */
	class CpuInstructionOpSED : public CpuInstructionBase
	{
	public:
		/**
		 * Create a new SED instruction
		 * @param	cpuRef				Reference to the CPU object
		 * @param	addressingMode		Addressing mode used for this instruction
		 */
		CpuInstructionOpSED(CPU& cpuRef, AddressingMode addressingMode);

	protected:
		/**
		 * Perform set decimal flag
		 */
		void ExecuteImpl() final override;
	};
}

#endif //! NES_CPU_INSTRUCTION_OP_SED_HPP
