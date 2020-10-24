#include "cpu_instruction_op_ldx.hpp"
#include "cpu/cpu.hpp"

#include <iostream>

nes::CpuInstructionOpLDX::CpuInstructionOpLDX(CPU& cpuRef, AddressingMode addressingMode) :
	CpuInstructionBase(cpuRef, addressingMode, "LDX")
{}

void nes::CpuInstructionOpLDX::ExecuteImpl()
{
	CpuRef.X = CpuRef.ReadRamValueAtAddress(CpuRef.GetTargetAddress(InstructionAddressingMode));
	CpuRef.UpdateZeroStatusFlag(CpuRef.X);
	CpuRef.UpdateNegativeStatusFlag(CpuRef.X);

	if (InstructionAddressingMode == AddressingMode::Immediate)
	{
		CycleCount = 2;
	}
	else if (InstructionAddressingMode == AddressingMode::ZeroPage)
	{
		CycleCount = 3;
	}
	else if (InstructionAddressingMode == AddressingMode::ZeroPageY || InstructionAddressingMode == AddressingMode::Absolute)
	{
		CycleCount = 4;
	}
	else if (InstructionAddressingMode == AddressingMode::AbsoluteY)
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
		std::cerr << "LDX - Unknown addressing mode.\n";
	}
}
