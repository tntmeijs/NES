#include "cpu_instruction_op_cld.hpp"
#include "cpu/cpu.hpp"

nes::CpuInstructionOpCLD::CpuInstructionOpCLD(CPU& cpuRef, AddressingMode addressingMode) :
	CpuInstructionBase(cpuRef, addressingMode, "CLD")
{}

void nes::CpuInstructionOpCLD::ExecuteImpl()
{
	CpuRef.ClearStatusFlag(StatusFlags::DecimalMode);
	CycleCount = 2;
}
