#include "cpu_instruction_op_cli.hpp"
#include "cpu/cpu.hpp"

nes::CpuInstructionOpCLI::CpuInstructionOpCLI(CPU& cpuRef, AddressingMode addressingMode) :
	CpuInstructionBase(cpuRef, addressingMode, "CLI")
{}

void nes::CpuInstructionOpCLI::ExecuteImpl()
{
	CpuRef.ClearStatusFlag(StatusFlags::InterruptDisable);
	CycleCount = 2;
}
