#include "cpu_instruction_op_dex.hpp"
#include "cpu/cpu.hpp"

nes::CpuInstructionOpDEX::CpuInstructionOpDEX(CPU& cpuRef, AddressingMode addressingMode) :
	CpuInstructionBase(cpuRef, addressingMode, "DEX")
{}

void nes::CpuInstructionOpDEX::ExecuteImpl()
{
	--CpuRef.X;
	CpuRef.UpdateZeroStatusFlag(CpuRef.X);
	CpuRef.UpdateNegativeStatusFlag(CpuRef.X);

	CycleCount = 2;
}
