#include "cpu_instruction_op_dec.hpp"
#include "cpu/cpu.hpp"

#include <iostream>

nes::CpuInstructionOpDEC::CpuInstructionOpDEC(CPU& cpuRef, AddressingMode addressingMode) :
	CpuInstructionBase(cpuRef, addressingMode, "DEC")
{}

void nes::CpuInstructionOpDEC::ExecuteImpl()
{
	std::uint16_t targetAddress = CpuRef.GetTargetAddress(InstructionAddressingMode);
	std::uint8_t value = CpuRef.ReadRamValueAtAddress(targetAddress);
	--value;
	CpuRef.WriteRamValueAtAddress(targetAddress, value);

	if (InstructionAddressingMode == AddressingMode::ZeroPage)
	{
		CycleCount = 5;
	}
	else if (InstructionAddressingMode == AddressingMode::ZeroPageX || InstructionAddressingMode == AddressingMode::Absolute)
	{
		CycleCount = 6;
	}
	else if (InstructionAddressingMode == AddressingMode::AbsoluteX)
	{
		CycleCount = 7;
	}
	else
	{
		std::cerr << "DEC - Unknown addressing mode.\n";
	}
}
