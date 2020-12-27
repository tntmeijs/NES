#include "cpu_instruction_op_rol.hpp"
#include "cpu/cpu.hpp"
#include "utility/bit_tools.hpp"

#include <iostream>

nes::CpuInstructionOpROL::CpuInstructionOpROL(CPU& cpuRef, AddressingMode addressingMode) :
	CpuInstructionBase(cpuRef, addressingMode, "ROL")
{}

void nes::CpuInstructionOpROL::ExecuteImpl()
{
	Byte valueToModify = CpuRef.A;

	if (InstructionAddressingMode != AddressingMode::Accumulator)
	{
		valueToModify = CpuRef.ReadRamValueAtAddress(CpuRef.GetTargetAddress(InstructionAddressingMode));
	}

	Byte old = valueToModify;

	// Shift left
	valueToModify.value <<= 1;

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
		CpuRef.WriteRamValueAtAddress(CpuRef.GetTargetAddress(InstructionAddressingMode), valueToModify);

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
