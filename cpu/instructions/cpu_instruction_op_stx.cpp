#include "cpu_instruction_op_stx.hpp"
#include "cpu/cpu.hpp"

#include <iostream>

nes::CpuInstructionOpSTX::CpuInstructionOpSTX(CPU& cpuRef, AddressingMode addressingMode) :
	CpuInstructionBase(cpuRef, addressingMode, "STX")
{}

void nes::CpuInstructionOpSTX::ExecuteImpl()
{
	CpuRef.WriteRamValueAtAddress(CpuRef.GetTargetAddress(InstructionAddressingMode), CpuRef.X);

	if (InstructionAddressingMode == AddressingMode::ZeroPage)
	{
		CycleCount = 3;
	}
	else if (InstructionAddressingMode == AddressingMode::ZeroPageY || InstructionAddressingMode == AddressingMode::Absolute)
	{
		CycleCount = 4;
	}
	else
	{
		std::cerr << "STX - Unknown addressing mode.\n";
	}
}
