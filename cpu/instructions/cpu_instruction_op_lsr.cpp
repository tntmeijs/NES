#include "cpu_instruction_op_lsr.hpp"
#include "cpu/cpu.hpp"

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
		std::uint8_t old = CpuRef.A;
		CpuRef.A = (CpuRef.A >> 1);

		if ((old & static_cast<std::uint8_t>(StatusFlags::Carry)) != 0)
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
		std::uint8_t value = CpuRef.ReadRamValueAtAddress(CpuRef.GetTargetAddress(InstructionAddressingMode));
		std::uint8_t old = value;
		value = (value >> 1);

		if ((old & static_cast<std::uint8_t>(StatusFlags::Carry)) != 0)
		{
			CpuRef.SetStatusFlag(StatusFlags::Carry);
		}
		else
		{
			CpuRef.ClearStatusFlag(StatusFlags::Carry);
		}

		CpuRef.UpdateZeroStatusFlag(value);
		CpuRef.UpdateNegativeStatusFlag(value);

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
