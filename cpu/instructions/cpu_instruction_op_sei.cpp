#include "cpu_instruction_op_sei.hpp"
#include "cpu/cpu.hpp"

nes::CpuInstructionOpSEI::CpuInstructionOpSEI(CPU& cpuRef, AddressingMode addressingMode) :
	CpuInstructionBase(cpuRef, addressingMode, "SEI")
{}

void nes::CpuInstructionOpSEI::ExecuteImpl()
{
	CpuRef.SetStatusFlag(StatusFlags::InterruptDisable);
	CycleCount = 2;
}
