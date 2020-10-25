#include "cpu_instruction_op_rts.hpp"
#include "cpu/cpu.hpp"
#include "utility/bit_tools.hpp"

nes::CpuInstructionOpRTS::CpuInstructionOpRTS(CPU& cpuRef, AddressingMode addressingMode) :
	CpuInstructionBase(cpuRef, addressingMode, "RTS")
{
	// Program counter is modified in the instruction, no need to do this in the
	// base class again
	AutoUpdateProgramCounter = false;
}

void nes::CpuInstructionOpRTS::ExecuteImpl()
{
	Byte lsb, msb;
	lsb = CpuRef.PopStack();
	msb = CpuRef.PopStack();
	std::uint16_t address = ConstructAddressFromBytes(msb, lsb);

	// Because JSR stores the target address - 1 on the stack, we have to add 1 to
	// the target address to get the location of the next instruction
	CpuRef.PC = address + 1;
	CycleCount = 6;
}
