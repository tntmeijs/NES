#include "cpu_instruction_op_cmp.hpp"
#include "cpu/cpu.hpp"

#include <iostream>

nes::CpuInstructionOpCMP::CpuInstructionOpCMP(CPU& cpuRef, AddressingMode addressingMode) :
	CpuInstructionBase(cpuRef, addressingMode, "CMP")
{}

void nes::CpuInstructionOpCMP::ExecuteImpl()
{
	std::uint8_t value = CpuRef.ReadRamValueAtAddress(CpuRef.GetTargetAddress(InstructionAddressingMode));
	std::uint8_t result = CpuRef.A - value;

	if (CpuRef.A >= value)
	{
		CpuRef.SetStatusFlag(StatusFlags::Carry);
	}
	else
	{
		CpuRef.ClearStatusFlag(StatusFlags::Carry);
	}

	CpuRef.UpdateZeroStatusFlag(CpuRef.A - value);
	CpuRef.UpdateNegativeStatusFlag(result);

	if (InstructionAddressingMode == AddressingMode::Immediate)
	{
		CycleCount = 2;
	}
	else if (InstructionAddressingMode == AddressingMode::ZeroPage)
	{
		CycleCount = 3;
	}
	else if (InstructionAddressingMode == AddressingMode::Absolute || InstructionAddressingMode == AddressingMode::ZeroPageX)
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
		std::cerr << "CMP - Unknown addressing mode.\n";
	}
}
