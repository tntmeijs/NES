#include "cpu_instruction_op_asl.hpp"
#include "cpu/cpu.hpp"
#include "utility/bit_tools.hpp"

nes::CpuInstructionOpASL::CpuInstructionOpASL(CPU& cpuRef, AddressingMode addressingMode) :
	CpuInstructionBase(cpuRef, addressingMode, "ASL")
{}

void nes::CpuInstructionOpASL::ExecuteImpl()
{
	// Assume the accumulator needs to be shifted
	Byte valueToShift = CpuRef.A;

	if (InstructionAddressingMode == AddressingMode::Accumulator)
	{
		CycleCount = 2;
	}
	else
	{
		// Need to shift in a memory location instead
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
			//#TODO: Find all std::cerr usages and replace it with EditorLogger::LogError()
		}
	}

	// Store old bit 7 in the carry flag
	if (IsNthBitSet(valueToShift, 7))
	{
		CpuRef.SetStatusFlag(StatusFlags::Carry);
	}
	else
	{
		CpuRef.ClearStatusFlag(StatusFlags::Carry);
	}

	// Shift all bits one place to the left
	valueToShift.value <<= 1;

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
