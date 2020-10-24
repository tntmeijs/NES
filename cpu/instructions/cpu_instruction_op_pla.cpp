#include "cpu_instruction_op_pla.hpp"
#include "cpu/cpu.hpp"

nes::CpuInstructionOpPLA::CpuInstructionOpPLA(CPU& cpuRef, AddressingMode addressingMode) :
	CpuInstructionBase(cpuRef, addressingMode, "PLA")
{}

void nes::CpuInstructionOpPLA::ExecuteImpl()
{
	CpuRef.A = CpuRef.PopStack();
	CpuRef.UpdateZeroStatusFlag(CpuRef.A);
	CpuRef.UpdateNegativeStatusFlag(CpuRef.A);
	CycleCount = 4;
}
