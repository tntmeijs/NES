#include "cpu_instruction_op_bpl.hpp"
#include "cpu/cpu.hpp"

nes::CpuInstructionOpBPL::CpuInstructionOpBPL(CPU& cpuRef, AddressingMode addressingMode) :
	CpuInstructionBase(cpuRef, addressingMode, "BPL")
{}

void nes::CpuInstructionOpBPL::ExecuteImpl()
{
	CycleCount = 2;

	// Negative flag is clear
	if (CpuRef.IsStatusFlagClear(StatusFlags::Negative))
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
