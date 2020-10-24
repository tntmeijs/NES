#include "cpu_instruction_op_inc.hpp"
#include "cpu/cpu.hpp"

#include <iostream>

nes::CpuInstructionOpINC::CpuInstructionOpINC(CPU& cpuRef, AddressingMode addressingMode) :
	CpuInstructionBase(cpuRef, addressingMode, "INC")
{}

void nes::CpuInstructionOpINC::ExecuteImpl()
{
	std::uint16_t address = CpuRef.GetTargetAddress(InstructionAddressingMode);

	// Increment and store the value at the specified address
	std::uint8_t value = (CpuRef.ReadRamValueAtAddress(address) + 1);
	CpuRef.WriteRamValueAtAddress(address, value);

	CpuRef.UpdateZeroStatusFlag(value);
	CpuRef.UpdateNegativeStatusFlag(value);

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
		std::cerr << "INC - Unknown addressing mode.\n";
	}
}
