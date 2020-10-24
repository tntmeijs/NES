#include "cpu_instruction_op_bit.hpp"
#include "cpu/cpu.hpp"

#include <iostream>

nes::CpuInstructionOpBIT::CpuInstructionOpBIT(CPU& cpuRef, AddressingMode addressingMode) :
	CpuInstructionBase(cpuRef, addressingMode, "BIT")
{}

void nes::CpuInstructionOpBIT::ExecuteImpl()
{
	std::uint8_t value = CpuRef.ReadRamValueAtAddress(CpuRef.GetTargetAddress(InstructionAddressingMode));

	if (InstructionAddressingMode == AddressingMode::ZeroPage)
	{
		CycleCount = 3;
	}
	else if (InstructionAddressingMode == AddressingMode::Absolute)
	{
		CycleCount = 4;
	}
	else
	{
		std::cerr << "BIT - Unknown addressing mode.\n";
	}

	CpuRef.UpdateZeroStatusFlag(CpuRef.A & value);
	CpuRef.UpdateNegativeStatusFlag(value);

	// Set the overflow flag to the value of the 6th bit
	if (CpuRef.IsNthBitSet(value, 6))
	{
		CpuRef.SetStatusFlag(StatusFlags::Overflow);
	}
	else
	{
		CpuRef.ClearStatusFlag(StatusFlags::Overflow);
	}
}
