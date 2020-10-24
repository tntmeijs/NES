#include "cpu_instruction_op_jmp.hpp"
#include "cpu/cpu.hpp"

#include <iostream>

nes::CpuInstructionOpJMP::CpuInstructionOpJMP(CPU& cpuRef, AddressingMode addressingMode) :
	CpuInstructionBase(cpuRef, addressingMode, "JMP")
{
	// Jump instructions modify the program counter already, no need to increment
	// it in the base class afterwards
	AutoUpdateProgramCounter = false;
}

void nes::CpuInstructionOpJMP::ExecuteImpl()
{
	CpuRef.SetProgramCounterToAddress(CpuRef.GetTargetAddress(InstructionAddressingMode));

	if (InstructionAddressingMode == AddressingMode::Absolute)
	{
		CycleCount = 3;
	}
	else if (InstructionAddressingMode == AddressingMode::Indirect)
	{
		CycleCount = 5;
	}
	else
	{
		std::cerr << "JMP - Unknown addressing mode.\n";
	}
}
