#ifndef NES_CPU_INSTRUCTION_OP_PHP_HPP
#define NES_CPU_INSTRUCTION_OP_PHP_HPP

#include "cpu_instruction_base.hpp"

namespace nes
{
	class CPU;

	/**
	 * Push processor status
	 */
	class CpuInstructionOpPHP : public CpuInstructionBase
	{
	public:
		/**
		 * Create a new PHP instruction
		 * @param	cpuRef				Reference to the CPU object
		 * @param	addressingMode		Addressing mode used for this instruction
		 */
		CpuInstructionOpPHP(CPU& cpuRef, AddressingMode addressingMode);

	protected:
		/**
		 * Perform push processor status
		 */
		void ExecuteImpl() final override;
	};
}

#endif //! NES_CPU_INSTRUCTION_OP_PHP_HPP
