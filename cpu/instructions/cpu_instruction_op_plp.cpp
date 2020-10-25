#include "cpu_instruction_op_plp.hpp"
#include "cpu/cpu.hpp"
#include "utility/bit_tools.hpp"

nes::CpuInstructionOpPLP::CpuInstructionOpPLP(CPU& cpuRef, AddressingMode addressingMode) :
	CpuInstructionBase(cpuRef, addressingMode, "PLP")
{}

void nes::CpuInstructionOpPLP::ExecuteImpl()
{
	Byte fromStack = CpuRef.PopStack();

	MatchBitStateOfNthBit(CpuRef.P, fromStack, 0);
	MatchBitStateOfNthBit(CpuRef.P, fromStack, 1);
	MatchBitStateOfNthBit(CpuRef.P, fromStack, 2);
	MatchBitStateOfNthBit(CpuRef.P, fromStack, 3);
	MatchBitStateOfNthBit(CpuRef.P, fromStack, 6);
	MatchBitStateOfNthBit(CpuRef.P, fromStack, 7);

	CycleCount = 4;
}
