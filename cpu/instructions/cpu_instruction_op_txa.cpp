#include "cpu_instruction_op_txa.hpp"
#include "cpu/cpu.hpp"

nes::CpuInstructionOpTXA::CpuInstructionOpTXA(CPU& cpuRef, AddressingMode addressingMode) :
	CpuInstructionBase(cpuRef, addressingMode, "TXA")
{}

void nes::CpuInstructionOpTXA::ExecuteImpl()
{
	CpuRef.A = CpuRef.X;
	CpuRef.UpdateZeroStatusFlag(CpuRef.A);
	CpuRef.UpdateNegativeStatusFlag(CpuRef.A);
	CycleCount = 2;
}
