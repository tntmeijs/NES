#include "cpu_instruction_op_bvc.hpp"
#include "cpu/cpu.hpp"

nes::CpuInstructionOpBVC::CpuInstructionOpBVC(CPU& cpuRef, AddressingMode addressingMode) :
	CpuInstructionBase(cpuRef, addressingMode, "BVC")
{}

void nes::CpuInstructionOpBVC::ExecuteImpl()
{
	CycleCount = 2;

	// Overflow flag is clear
	if (CpuRef.IsStatusFlagClear(StatusFlags::Overflow))
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
