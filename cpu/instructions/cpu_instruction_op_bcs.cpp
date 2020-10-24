#include "cpu_instruction_op_bcs.hpp"
#include "cpu/cpu.hpp"

nes::CpuInstructionOpBCS::CpuInstructionOpBCS(CPU& cpuRef, AddressingMode addressingMode) :
	CpuInstructionBase(cpuRef, addressingMode, "BCS")
{}

void nes::CpuInstructionOpBCS::ExecuteImpl()
{
	CycleCount = 2;

	// Carry flag is set
	if (CpuRef.IsStatusFlagSet(StatusFlags::Carry))
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
