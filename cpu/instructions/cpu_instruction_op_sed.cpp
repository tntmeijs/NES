#include "cpu_instruction_op_sed.hpp"
#include "cpu/cpu.hpp"

nes::CpuInstructionOpSED::CpuInstructionOpSED(CPU& cpuRef, AddressingMode addressingMode) :
	CpuInstructionBase(cpuRef, addressingMode, "SED")
{}

void nes::CpuInstructionOpSED::ExecuteImpl()
{
	CpuRef.SetStatusFlag(StatusFlags::DecimalMode);
	CycleCount = 2;
}
