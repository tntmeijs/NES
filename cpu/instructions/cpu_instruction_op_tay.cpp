#include "cpu_instruction_op_tay.hpp"
#include "cpu/cpu.hpp"

nes::CpuInstructionOpTAY::CpuInstructionOpTAY(CPU& cpuRef, AddressingMode addressingMode) :
	CpuInstructionBase(cpuRef, addressingMode, "TAY")
{}

void nes::CpuInstructionOpTAY::ExecuteImpl()
{
	CpuRef.Y = CpuRef.A;
	CpuRef.UpdateZeroStatusFlag(CpuRef.Y);
	CpuRef.UpdateNegativeStatusFlag(CpuRef.Y);
	CycleCount = 2;
}
