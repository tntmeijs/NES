#include "cpu_instruction_op_lsr.hpp"
#include "cpu/cpu.hpp"

nes::CpuInstructionOpLSR::CpuInstructionOpLSR(CPU& cpuRef, AddressingMode addressingMode) :
	CpuInstructionBase(cpuRef, addressingMode, "LSR")
{}

void nes::CpuInstructionOpLSR::ExecuteImpl()
{
}
