#include "cpu_instruction_op_ror.hpp"
#include "cpu/cpu.hpp"
#include "utility/bit_tools.hpp"

#include <iostream>

nes::CpuInstructionOpROR::CpuInstructionOpROR(CPU& cpuRef, AddressingMode addressingMode) :
	CpuInstructionBase(cpuRef, addressingMode, "ROR")
{}

void nes::CpuInstructionOpROR::ExecuteImpl()
{
	// Assume the accumulator needs to be shifted
	Byte valueToShift = CpuRef.A;

	if (InstructionAddressingMode != AddressingMode::Accumulator)
	{
		// Memory needs to be shifted instead
		valueToShift = CpuRef.ReadRamValueAtAddress(CpuRef.GetTargetAddress(InstructionAddressingMode));
	}

	// Save in a wider value to make shifting easier
	std::uint16_t wideValueToShift = valueToShift.value;

	if (CpuRef.IsStatusFlagSet(StatusFlags::Carry))
	{
		wideValueToShift |= (1 << 8);
	}

	// Store carry bit state so it can be restored later
	auto oldCarryWasSet = IsNthBitSet(valueToShift, 0);

	// Shift all bits to the right
	wideValueToShift >>= 1;

	// All relevant data should now be stored in the lower 8 bits
	valueToShift.value = wideValueToShift & 0xFF;

	// Update CPU flags
	CpuRef.UpdateZeroStatusFlag(valueToShift);
	CpuRef.UpdateNegativeStatusFlag(valueToShift);

	// Restore the carry bit state
	if (oldCarryWasSet)
	{
		CpuRef.SetStatusFlag(StatusFlags::Carry);
	}
	else
	{
		CpuRef.ClearStatusFlag(StatusFlags::Carry);
	}

	// Save the result
	if (InstructionAddressingMode == AddressingMode::Accumulator)
	{
		CpuRef.A = valueToShift;
		CycleCount = 2;
	}
	else
	{
		CpuRef.WriteRamValueAtAddress(CpuRef.GetTargetAddress(InstructionAddressingMode), valueToShift);

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
			//#TODO: Add editor logger here, perhaps use the base class for this
			//		 All instructions need this anyway
		}
	}
}
