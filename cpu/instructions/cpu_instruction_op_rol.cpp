#include "cpu_instruction_op_rol.hpp"
#include "cpu/cpu.hpp"
#include "utility/bit_tools.hpp"

#include <iostream>

nes::CpuInstructionOpROL::CpuInstructionOpROL(CPU& cpuRef, AddressingMode addressingMode) :
	CpuInstructionBase(cpuRef, addressingMode, "ROL")
{}

void nes::CpuInstructionOpROL::ExecuteImpl()
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

	// Shift left
	value = (value << 1);

	// Old bit 7 becomes the new carry bit
	if (IsNthBitSet(old, 7))
	{
		SetNthBitState(value, 0, true);
	}
	else
	{
		SetNthBitState(value, 0, false);
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
