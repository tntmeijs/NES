#include "cpu_instruction_op_cpy.hpp"
#include "cpu/cpu.hpp"

#include <iostream>

nes::CpuInstructionOpCPY::CpuInstructionOpCPY(CPU& cpuRef, AddressingMode addressingMode) :
	CpuInstructionBase(cpuRef, addressingMode, "CPY")
{}

void nes::CpuInstructionOpCPY::ExecuteImpl()
{
	std::uint8_t value = CpuRef.ReadRamValueAtAddress(CpuRef.GetTargetAddress(InstructionAddressingMode)).value;
	std::uint8_t result = CpuRef.Y.value - value;

	if (CpuRef.Y.value >= value)
	{
		CpuRef.SetStatusFlag(StatusFlags::Carry);
	}
	else
	{
		CpuRef.ClearStatusFlag(StatusFlags::Carry);
	}

	Byte zero;
	zero.value = CpuRef.Y.value - value;

	Byte negative;
	negative.value = result;

	CpuRef.UpdateZeroStatusFlag(zero);
	CpuRef.UpdateNegativeStatusFlag(negative);

	if (InstructionAddressingMode == AddressingMode::Immediate)
	{
		CycleCount = 2;
	}
	else if (InstructionAddressingMode == AddressingMode::ZeroPage)
	{
		CycleCount = 3;
	}
	else if (InstructionAddressingMode == AddressingMode::Absolute)
	{
		CycleCount = 4;
	}
	else
	{
		std::cerr << "CPY - Unknown addressing mode.\n";
	}
}
