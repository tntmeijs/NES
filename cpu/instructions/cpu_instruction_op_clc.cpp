#include "cpu_instruction_op_clc.hpp"
#include "cpu/cpu.hpp"

nes::CpuInstructionOpCLC::CpuInstructionOpCLC(CPU& cpuRef, AddressingMode addressingMode) :
	CpuInstructionBase(cpuRef, addressingMode, "CLC")
{}

void nes::CpuInstructionOpCLC::ExecuteImpl()
{
	CpuRef.ClearStatusFlag(StatusFlags::Carry);
	CycleCount = 2;
}
