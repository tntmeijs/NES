#include "cpu_instruction_op_sbc.hpp"
#include "cpu/cpu.hpp"

#include <iostream>

nes::CpuInstructionOpSBC::CpuInstructionOpSBC(CPU& cpuRef, AddressingMode addressingMode) :
	CpuInstructionBase(cpuRef, addressingMode, "SBC")
{}

void nes::CpuInstructionOpSBC::ExecuteImpl()
{
	std::uint8_t value = CpuRef.ReadRamValueAtAddress(CpuRef.GetTargetAddress(InstructionAddressingMode));

	// Same as ADC but we invert the bits of the value to turn ADC into SBC
	std::uint16_t sum = CpuRef.A + ~value + (CpuRef.P & static_cast<std::uint8_t>(StatusFlags::Carry));

	// Carry if we did not exceed the maximum value for a byte
	if (!(sum > 0xFF))
	{
		CpuRef.SetStatusFlag(StatusFlags::Carry);
	}
	else
	{
		CpuRef.ClearStatusFlag(StatusFlags::Carry);
	}

	// Same as ADC but we invert the bits of the value to turn ADC into SBC
	if ((~(CpuRef.A ^ ~value) & (CpuRef.A ^ sum) & static_cast<std::uint8_t>(StatusFlags::Negative)) != 0)
	{
		CpuRef.SetStatusFlag(StatusFlags::Overflow);
	}
	else
	{
		CpuRef.ClearStatusFlag(StatusFlags::Overflow);
	}

	CpuRef.UpdateZeroStatusFlag(static_cast<std::uint8_t>(sum));
	CpuRef.UpdateNegativeStatusFlag(static_cast<std::uint8_t>(sum));

	// Only save the lower 8 bits as the carry / overflow flags have been set by now
	CpuRef.A = static_cast<std::uint8_t>(sum);

	if (InstructionAddressingMode == AddressingMode::Immediate)
	{
		CycleCount = 2;
	}
	else if (InstructionAddressingMode == AddressingMode::ZeroPage)
	{
		CycleCount = 3;
	}
	else if (InstructionAddressingMode == AddressingMode::ZeroPageX || InstructionAddressingMode == AddressingMode::Absolute)
	{
		CycleCount = 4;
	}
	else if (InstructionAddressingMode == AddressingMode::AbsoluteX || InstructionAddressingMode == AddressingMode::AbsoluteY)
	{
		std::uint16_t initialPC = CpuRef.PC;
		std::uint16_t currentPC = initialPC + 3;
		CycleCount = 4;

		if (CpuRef.DidProgramCounterCrossPageBoundary(initialPC, currentPC))
		{
			++CycleCount;
		}
	}
	else if (InstructionAddressingMode == AddressingMode::IndirectX)
	{
		CycleCount = 6;
	}
	else if (InstructionAddressingMode == AddressingMode::IndirectY)
	{
		std::uint16_t initialPC = CpuRef.PC;
		std::uint16_t currentPC = initialPC + 2;
		CycleCount = 5;

		if (CpuRef.DidProgramCounterCrossPageBoundary(initialPC, currentPC))
		{
			++CycleCount;
		}
	}
	else
	{
		std::cerr << "SBC - Unknown addressing mode.\n";
	}
}
