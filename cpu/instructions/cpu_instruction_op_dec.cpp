#include "cpu_instruction_op_dec.hpp"
#include "cpu/cpu.hpp"

nes::CpuInstructionOpDEC::CpuInstructionOpDEC(CPU& cpuRef, AddressingMode addressingMode) :
	CpuInstructionBase(cpuRef, addressingMode, "DEC")
{}

void nes::CpuInstructionOpDEC::ExecuteImpl()
{
}
