#include "cpu_instruction_op_bmi.hpp"
#include "cpu/cpu.hpp"

#include <iostream>

nes::CpuInstructionOpBMI::CpuInstructionOpBMI(CPU& cpuRef, AddressingMode addressingMode) :
	CpuInstructionBase(cpuRef, addressingMode, "BMI")
{}

void nes::CpuInstructionOpBMI::ExecuteImpl()
{
	CycleCount = 2;

	// Negative flag is set
	if (CpuRef.IsStatusFlagSet(StatusFlags::Negative))
	{
		std::int8_t displacement = CpuRef.ReadRamValueAtAddress(CpuRef.PC + 1).value;

		std::uint16_t initialPC = CpuRef.PC;
		std::uint16_t currentPC = initialPC + displacement;

		// Perform branching
		CpuRef.MoveProgramCounter(displacement);

		if (CpuRef.DidProgramCounterCrossPageBoundary(initialPC, currentPC))
		{
			CycleCount += 2;
		}
		else
		{
			CycleCount += 1;
		}
	}
}
