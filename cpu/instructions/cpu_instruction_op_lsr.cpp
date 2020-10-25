#include "cpu_instruction_op_lsr.hpp"
#include "cpu/cpu.hpp"
#include "utility/bit_tools.hpp"

#include <iostream>

nes::CpuInstructionOpLSR::CpuInstructionOpLSR(CPU& cpuRef, AddressingMode addressingMode) :
	CpuInstructionBase(cpuRef, addressingMode, "LSR")
{}

void nes::CpuInstructionOpLSR::ExecuteImpl()
{
	if (InstructionAddressingMode == AddressingMode::Accumulator)
	{
		CycleCount = 2;
	
		// Need to shift in the accumulator
		Byte old = CpuRef.A;
		CpuRef.A.value = (CpuRef.A.value >> 1);

		if (IsNthBitSet(old, static_cast<std::uint8_t>(StatusFlags::Carry)))
		{
			CpuRef.SetStatusFlag(StatusFlags::Carry);
		}
		else
		{
			CpuRef.ClearStatusFlag(StatusFlags::Carry);
		}

		CpuRef.UpdateZeroStatusFlag(CpuRef.A);
		CpuRef.UpdateNegativeStatusFlag(CpuRef.A);
	}
	else
	{
		// Need to shift in a memory location
		Byte memoryValue = CpuRef.ReadRamValueAtAddress(CpuRef.GetTargetAddress(InstructionAddressingMode));
		Byte old = memoryValue;
		memoryValue.value = (memoryValue.value >> 1);

		if (IsNthBitSet(old, static_cast<std::uint8_t>(StatusFlags::Carry)))
		{
			CpuRef.SetStatusFlag(StatusFlags::Carry);
		}
		else
		{
			CpuRef.ClearStatusFlag(StatusFlags::Carry);
		}

		CpuRef.UpdateZeroStatusFlag(memoryValue);
		CpuRef.UpdateNegativeStatusFlag(memoryValue);

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
}
