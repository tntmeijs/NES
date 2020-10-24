#include "cpu_instruction_op_nop.hpp"
#include "cpu/cpu.hpp"

nes::CpuInstructionOpNOP::CpuInstructionOpNOP(CPU& cpuRef, AddressingMode addressingMode) :
	CpuInstructionBase(cpuRef, addressingMode, "NOP")
{}

void nes::CpuInstructionOpNOP::ExecuteImpl()
{
	CycleCount = 2;
}
