#include "cpu_instruction_op_ror.hpp"
#include "cpu/cpu.hpp"
#include "utility/bit_tools.hpp"

#include <iostream>

nes::CpuInstructionOpROR::CpuInstructionOpROR(CPU& cpuRef, AddressingMode addressingMode) :
	CpuInstructionBase(cpuRef, addressingMode, "ROR")
{}

void nes::CpuInstructionOpROR::ExecuteImpl()
{
	std::uint16_t address = CpuRef.GetTargetAddress(InstructionAddressingMode);
	std::uint8_t value = 0;

	if (InstructionAddressingMode == AddressingMode::Accumulator)
	{
		value = CpuRef.A;
	}
	else
	{
		value = CpuRef.ReadRamValueAtAddress(address);
	}

	std::uint8_t old = value;

	// Shift right
	value = (value >> 1);

	// Old bit 0 becomes the new carry bit
	if (IsNthBitSet(old, 0))
	{
		CpuRef.SetNthBit(value, 0, true);
	}
	else
	{
		CpuRef.SetNthBit(value, 0, false);
	}

	CpuRef.UpdateZeroStatusFlag(value);
	CpuRef.UpdateNegativeStatusFlag(value);

	if (InstructionAddressingMode == AddressingMode::Accumulator)
	{
		CpuRef.A = value;
		CycleCount = 2;
	}
	else
	{
		CpuRef.WriteRamValueAtAddress(address, value);

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
			std::cerr << "ROL - Unknown addressing mode.\n";
		}
	}
}
