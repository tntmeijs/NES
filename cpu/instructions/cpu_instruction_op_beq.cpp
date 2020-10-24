#include "cpu_instruction_op_beq.hpp"
#include "cpu/cpu.hpp"

nes::CpuInstructionOpBEQ::CpuInstructionOpBEQ(CPU& cpuRef, AddressingMode addressingMode) :
	CpuInstructionBase(cpuRef, addressingMode, "BEQ")
{}

void nes::CpuInstructionOpBEQ::ExecuteImpl()
{
	CycleCount = 2;

	// Zero flag is set
	if (CpuRef.IsStatusFlagSet(StatusFlags::Zero))
	{
		std::int8_t displacement = CpuRef.ReadRamValueAtAddress(CpuRef.PC + 1);

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
