#include "cpu_instruction_op_cpx.hpp"
#include "cpu/cpu.hpp"

#include <iostream>

nes::CpuInstructionOpCPX::CpuInstructionOpCPX(CPU& cpuRef, AddressingMode addressingMode) :
	CpuInstructionBase(cpuRef, addressingMode, "CPX")
{}

void nes::CpuInstructionOpCPX::ExecuteImpl()
{
	std::uint8_t value = CpuRef.ReadRamValueAtAddress(CpuRef.GetTargetAddress(InstructionAddressingMode)).value;
	std::uint8_t result = CpuRef.X.value - value;

	if (CpuRef.X.value >= value)
	{
		CpuRef.SetStatusFlag(StatusFlags::Carry);
	}
	else
	{
		CpuRef.ClearStatusFlag(StatusFlags::Carry);
	}

	Byte zero;
	zero.value = CpuRef.X.value - value;

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
		std::cerr << "CPX - Unknown addressing mode.\n";
	}
}
