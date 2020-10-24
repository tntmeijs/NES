#include "cpu_instruction_op_pha.hpp"
#include "cpu/cpu.hpp"

nes::CpuInstructionOpPHA::CpuInstructionOpPHA(CPU& cpuRef, AddressingMode addressingMode) :
	CpuInstructionBase(cpuRef, addressingMode, "PHA")
{}

void nes::CpuInstructionOpPHA::ExecuteImpl()
{
	CpuRef.PushStack(CpuRef.A);
	CycleCount = 3;
}
