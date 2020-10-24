#include "cpu_instruction_op_clv.hpp"
#include "cpu/cpu.hpp"

nes::CpuInstructionOpCLV::CpuInstructionOpCLV(CPU& cpuRef, AddressingMode addressingMode) :
	CpuInstructionBase(cpuRef, addressingMode, "CLV")
{}

void nes::CpuInstructionOpCLV::ExecuteImpl()
{
	CpuRef.ClearStatusFlag(StatusFlags::Overflow);
	CycleCount = 2;
}
