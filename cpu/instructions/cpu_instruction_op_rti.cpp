#include "cpu_instruction_op_rti.hpp"
#include "cpu/cpu.hpp"

nes::CpuInstructionOpRTI::CpuInstructionOpRTI(CPU& cpuRef, AddressingMode addressingMode) :
	CpuInstructionBase(cpuRef, addressingMode, "RTI")
{}

void nes::CpuInstructionOpRTI::ExecuteImpl()
{
}
