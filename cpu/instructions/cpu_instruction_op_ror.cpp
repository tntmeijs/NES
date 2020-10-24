#include "cpu_instruction_op_ror.hpp"
#include "cpu/cpu.hpp"

nes::CpuInstructionOpROR::CpuInstructionOpROR(CPU& cpuRef, AddressingMode addressingMode) :
	CpuInstructionBase(cpuRef, addressingMode, "ROR")
{}

void nes::CpuInstructionOpROR::ExecuteImpl()
{
}
