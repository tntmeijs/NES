#include "cpu_instruction_op_sty.hpp"
#include "cpu/cpu.hpp"

#include <iostream>

nes::CpuInstructionOpSTY::CpuInstructionOpSTY(CPU& cpuRef, AddressingMode addressingMode) :
	CpuInstructionBase(cpuRef, addressingMode, "STY")
{}

void nes::CpuInstructionOpSTY::ExecuteImpl()
{
	CpuRef.WriteRamValueAtAddress(CpuRef.GetTargetAddress(InstructionAddressingMode), CpuRef.Y);

	if (InstructionAddressingMode == AddressingMode::ZeroPage)
	{
		CycleCount = 3;
	}
	else if (InstructionAddressingMode == AddressingMode::ZeroPageX || InstructionAddressingMode == AddressingMode::Absolute)
	{
		CycleCount = 4;
	}
	else
	{
		std::cerr << "STY - Unknown addressing mode.\n";
	}
}
