#include "cpu_instruction_op_brk.hpp"
#include "cpu/cpu.hpp"

nes::CpuInstructionOpBRK::CpuInstructionOpBRK(CPU& cpuRef, AddressingMode addressingMode) :
	CpuInstructionBase(cpuRef, addressingMode, "BRK")
{
	AutoUpdateProgramCounter = false;
}

void nes::CpuInstructionOpBRK::ExecuteImpl()
{
	CycleCount = 7;

	// Turn program counter into two bytes so it can be pushed to the stack
	std::uint8_t lsb = (CpuRef.PC & 0x00FF);
	std::uint8_t msb = ((CpuRef.PC & 0xFF00) >> 8);

	// Save state on the stack
	CpuRef.PushStack(msb);
	CpuRef.PushStack(lsb);
	CpuRef.PushStack(CpuRef.P);
	CpuRef.P |= (1 << 4);

	// Set program counter to the IRQ interrupt vector at 0xFFFE and 0xFFFF
	lsb = CpuRef.ReadRamValueAtAddress(0xFFFE);
	msb = CpuRef.ReadRamValueAtAddress(0xFFFF);
	CpuRef.PC = (((msb) >> 8) | lsb);
}
