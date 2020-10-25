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
	Byte valueToModify;

	if (InstructionAddressingMode == AddressingMode::Accumulator)
	{
		valueToModify = CpuRef.A;
	}
	else
	{
		valueToModify = CpuRef.ReadRamValueAtAddress(address);
	}

	Byte old = valueToModify;

	// Shift right
	valueToModify.value = (valueToModify.value >> 1);

	// Old bit 0 becomes the new carry bit
	if (IsNthBitSet(old, 0))
	{
		SetNthBitState(valueToModify, 0, true);
	}
	else
	{
		SetNthBitState(valueToModify, 0, false);
	}

	CpuRef.UpdateZeroStatusFlag(valueToModify);
	CpuRef.UpdateNegativeStatusFlag(valueToModify);

	if (InstructionAddressingMode == AddressingMode::Accumulator)
	{
		CpuRef.A = valueToModify;
		CycleCount = 2;
	}
	else
	{
		CpuRef.WriteRamValueAtAddress(address, valueToModify);

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
