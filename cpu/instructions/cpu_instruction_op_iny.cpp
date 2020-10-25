#include "cpu_instruction_op_iny.hpp"
#include "cpu/cpu.hpp"

nes::CpuInstructionOpINY::CpuInstructionOpINY(CPU& cpuRef, AddressingMode addressingMode) :
	CpuInstructionBase(cpuRef, addressingMode, "INY")
{}

void nes::CpuInstructionOpINY::ExecuteImpl()
{
	++CpuRef.Y.value;
	CpuRef.UpdateZeroStatusFlag(CpuRef.Y);
	CpuRef.UpdateNegativeStatusFlag(CpuRef.Y);

	CycleCount = 2;
}
