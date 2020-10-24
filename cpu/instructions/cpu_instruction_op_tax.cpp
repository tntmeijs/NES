#include "cpu_instruction_op_tax.hpp"
#include "cpu/cpu.hpp"

nes::CpuInstructionOpTAX::CpuInstructionOpTAX(CPU& cpuRef, AddressingMode addressingMode) :
	CpuInstructionBase(cpuRef, addressingMode, "TAX")
{}

void nes::CpuInstructionOpTAX::ExecuteImpl()
{
	CpuRef.X = CpuRef.A;
	CpuRef.UpdateZeroStatusFlag(CpuRef.X);
	CpuRef.UpdateNegativeStatusFlag(CpuRef.X);
	CycleCount = 2;
}
