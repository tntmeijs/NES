#include "cpu_instruction_op_rti.hpp"
#include "cpu/cpu.hpp"

nes::CpuInstructionOpRTI::CpuInstructionOpRTI(CPU& cpuRef, AddressingMode addressingMode) :
	CpuInstructionBase(cpuRef, addressingMode, "RTI")
{
	AutoUpdateProgramCounter = false;
}

void nes::CpuInstructionOpRTI::ExecuteImpl()
{
	CycleCount = 6;

	CpuRef.P = CpuRef.PopStack();
	std::uint8_t msb = CpuRef.PopStack();
	std::uint8_t lsb = CpuRef.PopStack();
	CpuRef.PC = ((msb >> 8) | lsb);
}
