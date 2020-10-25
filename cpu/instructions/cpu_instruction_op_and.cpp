#include "cpu_instruction_op_and.hpp"
#include "cpu/cpu.hpp"

#include <iostream>

nes::CpuInstructionOpAND::CpuInstructionOpAND(CPU& cpuRef, AddressingMode addressingMode) :
	CpuInstructionBase(cpuRef, addressingMode, "AND")
{}

void nes::CpuInstructionOpAND::ExecuteImpl()
{
	// Retrieve value to AND against the accumulator
	std::uint8_t compareAgainst = CpuRef.ReadRamValueAtAddress(CpuRef.GetTargetAddress(InstructionAddressingMode)).value;

	// Perform logical AND
	CpuRef.A.value &= compareAgainst;

	CpuRef.UpdateNegativeStatusFlag(CpuRef.A);
	CpuRef.UpdateZeroStatusFlag(CpuRef.A);

	if (InstructionAddressingMode == AddressingMode::Immediate)
	{
		CycleCount = 2;
	}
	else if (InstructionAddressingMode == AddressingMode::ZeroPage)
	{
		CycleCount = 3;
	}
	else if (InstructionAddressingMode == AddressingMode::ZeroPageX)
	{
		CycleCount = 4;
	}
	else if (InstructionAddressingMode == AddressingMode::Absolute)
	{
		CycleCount = 4;
	}
	else if (InstructionAddressingMode == AddressingMode::AbsoluteX || InstructionAddressingMode == AddressingMode::AbsoluteY)
	{
		std::uint16_t initialPC = CpuRef.PC;
		std::uint16_t currentPC = initialPC += 3;
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
		std::uint16_t currentPC = initialPC += 2;
		CycleCount = 5;

		if (CpuRef.DidProgramCounterCrossPageBoundary(initialPC, currentPC))
		{
			++CycleCount;
		}
	}
	else
	{
		std::cerr << "AND - Unknown addressing mode.\n";
	}
}
