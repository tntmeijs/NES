#include "cpu_instruction_op_ldy.hpp"
#include "cpu/cpu.hpp"

#include <iostream>

nes::CpuInstructionOpLDY::CpuInstructionOpLDY(CPU& cpuRef, AddressingMode addressingMode) :
	CpuInstructionBase(cpuRef, addressingMode, "LDY")
{}

void nes::CpuInstructionOpLDY::ExecuteImpl()
{
	CpuRef.Y = CpuRef.ReadRamValueAtAddress(CpuRef.GetTargetAddress(InstructionAddressingMode));
	CpuRef.UpdateZeroStatusFlag(CpuRef.Y);
	CpuRef.UpdateNegativeStatusFlag(CpuRef.Y);

	if (InstructionAddressingMode == AddressingMode::Immediate)
	{
		CycleCount = 2;
	}
	else if (InstructionAddressingMode == AddressingMode::ZeroPage)
	{
		CycleCount = 3;
	}
	else if (InstructionAddressingMode == AddressingMode::ZeroPageX || InstructionAddressingMode == AddressingMode::Absolute)
	{
		CycleCount = 4;
	}
	else if (InstructionAddressingMode == AddressingMode::AbsoluteX)
	{
		std::uint16_t initialPC = CpuRef.PC;
		std::uint16_t currentPC = initialPC + 3;
		CycleCount = 4;

		// Crossed a page boundary
		if (CpuRef.DidProgramCounterCrossPageBoundary(initialPC, currentPC))
		{
			++CycleCount;
		}
	}
	else
	{
		std::cerr << "LDY - Unknown addressing InstructionAddressingMode.\n";
	}
}
