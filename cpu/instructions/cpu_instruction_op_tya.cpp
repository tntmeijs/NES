#include "cpu_instruction_op_tya.hpp"
#include "cpu/cpu.hpp"

nes::CpuInstructionOpTYA::CpuInstructionOpTYA(CPU& cpuRef, AddressingMode addressingMode) :
	CpuInstructionBase(cpuRef, addressingMode, "TYA")
{}

void nes::CpuInstructionOpTYA::ExecuteImpl()
{
	CpuRef.A = CpuRef.Y;
	CpuRef.UpdateZeroStatusFlag(CpuRef.A);
	CpuRef.UpdateNegativeStatusFlag(CpuRef.A);
	CycleCount = 2;
}
