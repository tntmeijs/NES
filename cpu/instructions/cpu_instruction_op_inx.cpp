#include "cpu_instruction_op_inx.hpp"
#include "cpu/cpu.hpp"

nes::CpuInstructionOpINX::CpuInstructionOpINX(CPU& cpuRef, AddressingMode addressingMode) :
	CpuInstructionBase(cpuRef, addressingMode, "INX")
{}

void nes::CpuInstructionOpINX::ExecuteImpl()
{
	++CpuRef.X;
	CpuRef.UpdateZeroStatusFlag(CpuRef.X);
	CpuRef.UpdateNegativeStatusFlag(CpuRef.X);

	CycleCount = 2;
}
