#include "cpu_instruction_op_jsr.hpp"
#include "cpu/cpu.hpp"
#include "utility/bit_tools.hpp"

#include <iostream>

nes::CpuInstructionOpJSR::CpuInstructionOpJSR(CPU& cpuRef, AddressingMode addressingMode) :
	CpuInstructionBase(cpuRef, addressingMode, "JSR")
{
	// Jump instructions modify the program counter already, no need to increment
	// it in the base class afterwards
	AutoUpdateProgramCounter = false;
}

void nes::CpuInstructionOpJSR::ExecuteImpl()
{
	if (InstructionAddressingMode == AddressingMode::Absolute)
	{
		// The JSR instruction is 3 bytes wide, this would mean that the next
		// instruction is at PC + 3. However, the documentation states that JSR
		// pushes (next instruction - 1) to the stack, hence we only add two bytes
		// instead of three. This is to account for that -1.
		std::uint16_t returnAddress = CpuRef.PC + 2;

		// Store the target address minus one on the stack
		Byte lsb, msb;
		lsb.value = (returnAddress & 0x00FF);
		msb.value = ((returnAddress & 0xFF00) >> 8);

		// According to the documentation, the high byte needs to be pushed first
		CpuRef.PushStack(msb);
		CpuRef.PushStack(lsb);

		// Jump to the target location
		CpuRef.PC = CpuRef.GetTargetAddress(InstructionAddressingMode);
		CycleCount = 6;
	}
	else
	{
		std::cerr << "JSR - Unknown addressing mode.\n";
	}
}
