#include "cpu_instruction_op_lsr.hpp"
#include "cpu/cpu.hpp"
#include "utility/bit_tools.hpp"

#include <iostream>

nes::CpuInstructionOpLSR::CpuInstructionOpLSR(CPU& cpuRef, AddressingMode addressingMode) :
	CpuInstructionBase(cpuRef, addressingMode, "LSR")
{}

void nes::CpuInstructionOpLSR::ExecuteImpl()
{
	Byte valueToShift = {};

	if (InstructionAddressingMode == AddressingMode::Accumulator)
	{
		CycleCount = 2;
	
		// Need to shift in the accumulator
		valueToShift = CpuRef.A;
	}
	else
	{
		// Need to shift in a memory location
		Byte valueToShift = CpuRef.ReadRamValueAtAddress(CpuRef.GetTargetAddress(InstructionAddressingMode));

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
			std::cerr << "LSR - Unknown addressing mode.\n";
		}
	}

	// Store old bit 0 in the carry flag
	if (IsNthBitSet(valueToShift, 0))
	{
		CpuRef.SetStatusFlag(StatusFlags::Carry);
	}
	else
	{
		CpuRef.ClearStatusFlag(StatusFlags::Carry);
	}

	// Shift all bits one place to the right
	valueToShift.value >>= 1;

	// Update flags
	CpuRef.UpdateZeroStatusFlag(valueToShift);
	CpuRef.UpdateNegativeStatusFlag(valueToShift);

	// Save the result
	if (InstructionAddressingMode == AddressingMode::Accumulator)
	{
		CpuRef.A = valueToShift;
	}
	else
	{
		CpuRef.WriteRamValueAtAddress(CpuRef.GetTargetAddress(InstructionAddressingMode), valueToShift);
	}
}
