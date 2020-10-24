#include "cpu_instruction_op_rol.hpp"
#include "cpu/cpu.hpp"

nes::CpuInstructionOpROL::CpuInstructionOpROL(CPU& cpuRef, AddressingMode addressingMode) :
	CpuInstructionBase(cpuRef, addressingMode, "ROL")
{}

void nes::CpuInstructionOpROL::ExecuteImpl()
{
}
