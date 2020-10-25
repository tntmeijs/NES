#include "cpu_instruction_op_dec.hpp"
#include "cpu/cpu.hpp"
#include "utility/bit_tools.hpp"

#include <iostream>

nes::CpuInstructionOpDEC::CpuInstructionOpDEC(CPU& cpuRef, AddressingMode addressingMode) :
	CpuInstructionBase(cpuRef, addressingMode, "DEC")
{}

void nes::CpuInstructionOpDEC::ExecuteImpl()
{
	std::uint16_t targetAddress = CpuRef.GetTargetAddress(InstructionAddressingMode);
	Byte ramValue = CpuRef.ReadRamValueAtAddress(targetAddress);
	--ramValue.value;
	CpuRef.WriteRamValueAtAddress(targetAddress, ramValue);

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
