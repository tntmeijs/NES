#include "cpu_instruction_op_asl.hpp"

#include <iostream>

nes::CpuInstructionOpASL::CpuInstructionOpASL(CPU& cpuRef, AddressingMode addressingMode) :
	CpuInstructionBase(cpuRef, addressingMode, "ASL")
{}

void nes::CpuInstructionOpASL::ExecuteImpl()
{
	// Not implemented
}
