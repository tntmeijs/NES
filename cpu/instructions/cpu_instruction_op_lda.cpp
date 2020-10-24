#include "cpu_instruction_op_lda.hpp"
#include "cpu/cpu.hpp"

#include <iostream>

nes::CpuInstructionOpLDA::CpuInstructionOpLDA(CPU& cpuRef, AddressingMode addressingMode) :
	CpuInstructionBase(cpuRef, addressingMode, "LDA")
{}

void nes::CpuInstructionOpLDA::ExecuteImpl()
{
	CpuRef.A = CpuRef.ReadRamValueAtAddress(CpuRef.GetTargetAddress(InstructionAddressingMode));
	CpuRef.UpdateZeroStatusFlag(CpuRef.A);
	CpuRef.UpdateNegativeStatusFlag(CpuRef.A);

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

		// Crossed a page boundary
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

		// Crossed a page boundary
		if (CpuRef.DidProgramCounterCrossPageBoundary(initialPC, currentPC))
		{
			++CycleCount;
		}
	}
	else
	{
		std::cerr << "LDA - Unknown addressing mode.\n";
	}
}
