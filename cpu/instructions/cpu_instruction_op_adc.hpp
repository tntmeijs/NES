#ifndef NES_CPU_INSTRUCTION_OP_ADC_HPP
#define NES_CPU_INSTRUCTION_OP_ADC_HPP

#include "cpu_instruction_base.hpp"

namespace nes
{
	class CPU;

	/**
	 * Add with carry
	 */
	class CpuInstructionOpADC : public CpuInstructionBase
	{
	public:
		/**
		 * Create a new ADC instruction
		 * @param	cpuRef				Reference to the CPU object
		 * @param	addressingMode		Addressing mode used for this instruction
		 */
		CpuInstructionOpADC(CPU& cpuRef, AddressingMode addressingMode);

	protected:
		/**
		 * Perform add with carry
		 */
		void ExecuteImpl() final override;
	};
}

#endif //! NES_CPU_INSTRUCTION_OP_ADC_HPP
