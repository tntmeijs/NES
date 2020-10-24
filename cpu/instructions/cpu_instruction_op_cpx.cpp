#include "cpu_instruction_op_cpx.hpp"
#include "cpu/cpu.hpp"

#include <iostream>

nes::CpuInstructionOpCPX::CpuInstructionOpCPX(CPU& cpuRef, AddressingMode addressingMode) :
	CpuInstructionBase(cpuRef, addressingMode, "CPX")
{}

void nes::CpuInstructionOpCPX::ExecuteImpl()
{
	std::uint8_t value = CpuRef.ReadRamValueAtAddress(CpuRef.GetTargetAddress(InstructionAddressingMode));
	std::uint8_t result = CpuRef.X - value;

	if (CpuRef.X >= value)
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
	else if (InstructionAddressingMode == AddressingMode::Absolute)
	{
		CycleCount = 4;
	}
	else
	{
		std::cerr << "CPX - Unknown addressing mode.\n";
	}
}
