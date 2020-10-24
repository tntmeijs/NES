#include "cpu_instruction_op_dey.hpp"
#include "cpu/cpu.hpp"

nes::CpuInstructionOpDEY::CpuInstructionOpDEY(CPU& cpuRef, AddressingMode addressingMode) :
	CpuInstructionBase(cpuRef, addressingMode, "DEY")
{}

void nes::CpuInstructionOpDEY::ExecuteImpl()
{
	--CpuRef.Y;
	CpuRef.UpdateZeroStatusFlag(CpuRef.Y);
	CpuRef.UpdateNegativeStatusFlag(CpuRef.Y);

	CycleCount = 2;
}
