#include "cpu_instruction_op_sta.hpp"
#include "cpu/cpu.hpp"

#include <iostream>

nes::CpuInstructionOpSTA::CpuInstructionOpSTA(CPU& cpuRef, AddressingMode addressingMode) :
	CpuInstructionBase(cpuRef, addressingMode, "STA")
{}

void nes::CpuInstructionOpSTA::ExecuteImpl()
{
	CpuRef.WriteRamValueAtAddress(CpuRef.GetTargetAddress(InstructionAddressingMode), CpuRef.A);

	if (InstructionAddressingMode == AddressingMode::ZeroPage)
	{
		CycleCount = 3;
	}
	else if (InstructionAddressingMode == AddressingMode::ZeroPageX || InstructionAddressingMode == AddressingMode::Absolute)
	{
		CycleCount = 4;
	}
	else if (InstructionAddressingMode == AddressingMode::AbsoluteX || InstructionAddressingMode == AddressingMode::AbsoluteY)
	{
		CycleCount = 5;
	}
	else if (InstructionAddressingMode == AddressingMode::IndirectX || InstructionAddressingMode == AddressingMode::IndirectY)
	{
		CycleCount = 6;
	}
	else
	{
		std::cerr << "STA - Unknown addressing mode.\n";
	}
}
