#include "cpu_instruction_op_bcc.hpp"
#include "cpu/cpu.hpp"

nes::CpuInstructionOpBCC::CpuInstructionOpBCC(CPU& cpuRef, AddressingMode addressingMode) :
	CpuInstructionBase(cpuRef, addressingMode, "BCC")
{}

void nes::CpuInstructionOpBCC::ExecuteImpl()
{
	CycleCount = 2;

	// Carry flag is clear
	if (CpuRef.IsStatusFlagClear(StatusFlags::Carry))
	{
		std::int8_t displacement = CpuRef.ReadRamValueAtAddress(CpuRef.PC + 1).value;
		
		std::uint16_t initialPC = CpuRef.PC;
		std::uint16_t currentPC = initialPC += displacement;

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
