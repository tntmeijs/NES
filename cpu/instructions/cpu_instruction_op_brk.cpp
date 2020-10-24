#include "cpu_instruction_op_brk.hpp"

#include <iostream>

nes::CpuInstructionOpBRK::CpuInstructionOpBRK(CPU& cpuRef, AddressingMode addressingMode) :
	CpuInstructionBase(cpuRef, addressingMode, "BRK")
{}

void nes::CpuInstructionOpBRK::ExecuteImpl()
{
	// Not implemented
}
