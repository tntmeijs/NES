#include "cpu_instruction_op_tsx.hpp"
#include "cpu/cpu.hpp"

nes::CpuInstructionOpTSX::CpuInstructionOpTSX(CPU& cpuRef, AddressingMode addressingMode) :
	CpuInstructionBase(cpuRef, addressingMode, "TSX")
{}

void nes::CpuInstructionOpTSX::ExecuteImpl()
{
	CpuRef.X = CpuRef.SP;
	CpuRef.UpdateZeroStatusFlag(CpuRef.X);
	CpuRef.UpdateNegativeStatusFlag(CpuRef.X);
	CycleCount = 2;
}
