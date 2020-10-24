#include "cpu_instruction_op_sec.hpp"
#include "cpu/cpu.hpp"

nes::CpuInstructionOpSEC::CpuInstructionOpSEC(CPU& cpuRef, AddressingMode addressingMode) :
	CpuInstructionBase(cpuRef, addressingMode, "SEC")
{}

void nes::CpuInstructionOpSEC::ExecuteImpl()
{
	CpuRef.SetStatusFlag(StatusFlags::Carry);
	CycleCount = 2;
}
