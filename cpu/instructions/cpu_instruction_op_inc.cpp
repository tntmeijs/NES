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
	Byte valueAtAddress = CpuRef.ReadRamValueAtAddress(address);
	++valueAtAddress.value;
	CpuRef.WriteRamValueAtAddress(address, valueAtAddress);

	CpuRef.UpdateZeroStatusFlag(valueAtAddress);
	CpuRef.UpdateNegativeStatusFlag(valueAtAddress);

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
