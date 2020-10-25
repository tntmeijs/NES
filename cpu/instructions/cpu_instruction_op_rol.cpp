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

	// Shift left
	valueToModify.value = (valueToModify.value << 1);

	// Old bit 7 becomes the new carry bit
	valueToModify.bit0 = old.bit7;

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
